/*!
* \file skinwindowprompt.js
* \brief File containing skin window prompt flags
*/

/*!
* \class SkinWindowPromptType
* \brief Skin window prompt question and return type flags
*/

function SkinWindowPrompt() {
    /*!
    * Unknown
    * \type int
    */
    this.UNKNOWN = 0;
    /*!
    * Ok
    * \type int
    */
    this.OK = 1;
    /*!
    * Cancel
    * \type int
    */
    this.CANCEL = 2;
    /*!
    * Yes
    * \type int
    */
    this.YES = 4;
    /*!
    * No
    * \type int
    */
    this.NO = 8;
}

/*!
* converts a skin window prompt flags to a string
* \tparam string id prompt flag
* \type string
* \returns stringified name of prompt flag
*/
SkinWindowPrompt.prototype.nameFromId = function(id) {
    var nameMap = [
        "Ok",
        "Cancel",
        "Yes",
        "No",
    ];

    return nameMap[id];
};

/*!
* precreated global instance of SkinWindowPrompt
* \type SkinWindowPrompt
*/
var skinWindowPrompt = new SkinWindowPrompt();
