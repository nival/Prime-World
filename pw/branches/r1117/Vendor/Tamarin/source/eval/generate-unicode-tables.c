/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is [Open Source Virtual Machine.].
 *
 * The Initial Developer of the Original Code is
 * Adobe System Incorporated.
 * Portions created by the Initial Developer are Copyright (C) 2008
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Adobe AS3 Team
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

/* Generate simple lookup tables from the unicode table.
 * Below, 'UnicodeData.txt' is the data file downloaded from unicode.org.
 *
 * Compile this program:
 *   cc -o ranges ranges.c
 *
 * Extract the desired data rows:
 *   egrep ';(Lu|Ll|Lt|Lm|Lo|Nl);' UnicodeData.txt > IdentifierStart.txt
 *
 * Generate data definitions:
 *   ranges IdentifierStart.txt identifier_start > identifier_start.h
 *
 * All character values in the range above 0xFFFF are ignored.
 *
 * The table encodings are straightforward.  It's possible to code the
 * tables more efficiently if the high value of a range can be a delta
 * to the low value, and if the low value of the next range can be a
 * delta to the high of the previous range.  For the identifier_start
 * table the storage can be cut in half, pretty much.  The function
 * 'analyze()' computes statistics for these.  It should also be
 * possible to store the singleton table as delta values, but I've not
 * examined this.
 */

#include <stdio.h>
#include <string.h>

struct { int lo, hi; } ranges[10000];
int next_range = 0;

int singletons[10000];
int next_singleton = 0;

int exceptions[10000];
int next_exception = 0;

void enter(int lo, int hi)
{
    if (lo < hi) {
	ranges[next_range].lo = lo;
	ranges[next_range].hi = hi;
	next_range++;
    }
    else
	singletons[next_singleton++] = lo;
}

/* This analysis tries to merge ranges that are close together by
 * placing the values that aren't in the merged range into an
 * exception table.  It didn't pay off for ECMAScript identifier data;
 * no ranges were merged with the criteria used here.
 */
/*
void merge()
{
    int i=0, j=0, k;
    while (j < next_range) {
	if (ranges[j].lo - ranges[i].hi <= 3) {
	    for ( k=ranges[i].hi+1 ; k <= ranges[j].lo-1 ; k++ )
		exceptions[next_exception++] = k;
	    ranges[i].hi = ranges[j].hi;
	    ranges[j].lo = ranges[j].hi = -2;
	    j++;
	}
	else
	    i = ++j;
    }
}
*/

void analyze()
{
    int i, j;
    int wide = 0;
    int wide_gap = 0;

    for ( i=0 ; i < next_range ; i++ )
	if (ranges[i].hi - ranges[i].lo > 254)
	    wide++;
    printf("Narrow ranges: %d\n", next_range - wide);
    printf("Wide ranges: %d\n", wide);
    for ( i=1 ; i < next_range ; i++ )
	if (ranges[i-1].hi - ranges[i].lo > 255)
	    wide_gap++;
    printf("Narrow gaps: %d\n", (next_range - 1) - wide_gap);
    printf("Wide gaps: %d\n", wide_gap);
}

void print(const char* prefix)
{
    int i, numranges=0;

    for ( i=0 ; i < next_range ; i++ )
	if (ranges[i].lo != -2)
	    ++numranges;

    printf("static const uint16_t %s_ranges[][2] = {\n", prefix);
    for ( i=0 ; i < next_range ; i++ )
	if (ranges[i].lo != -2)
	    printf("{0x%04X, 0x%04X},\n", ranges[i].lo, ranges[i].hi);
    printf("};\n\n");

    printf("static const uint16_t %s_singletons[] = {\n", prefix);
    for ( i=0 ; i < next_singleton; i++ )
	printf("0x%04X,\n", singletons[i]);
    printf("};\n\n");

    printf("static const unicode_table_t %s = {\n", prefix);
    printf("    %d,\n", numranges);
    printf("    %s_ranges,\n", prefix);
    printf("    %d,\n", next_singleton);
    printf("    %s_singletons\n", prefix);
    printf("};\n");
}

int main(int argc, char** argv)
{
    char buf[500];

    if (argc != 3)
	goto fail;

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL)
	goto fail;

    int lo, hi;
    hi = -2;
    while (fgets(buf, sizeof(buf), fp) != NULL) {
	int n;
	buf[sizeof(buf)-1] = 0;
	if (strlen(buf) == sizeof(buf)-1)
	    goto fail;
	if (sscanf(buf, "%x;", &n) != 1)
	    goto fail;
	if (n > 0xFFFF)
	    break;
	if (n == hi+1)
	    hi = n;
	else {
	    if (hi != -2) 
		enter(lo, hi);
	    lo=hi=n;
	}
    }
    if (hi != -2)
	enter(lo, hi);

    fclose(fp);

    //merge();
    //analyze();
    print(argv[2]);

    return 0;

 fail:
    printf("Failure.\n");
    return 1;
}
