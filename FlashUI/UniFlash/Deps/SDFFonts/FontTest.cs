using UnityEngine;

namespace SDFFonts
{
    [RequireComponent(typeof(MeshFilter))]
    public class FontTest : MonoBehaviour
    {
        public string sampleText;

        private MeshFilter _mf;
        private Font _font;

        private void Awake()
        {
            if (!Application.isEditor)
                return;

            _mf = gameObject.GetComponent<MeshFilter>();
        }

        private void Update()
        {
            if (!Application.isEditor)
                return;

            _font = FontManager.Instance["DejaVu", FontStyle.Normal];

            GenerateTextMesh();
        }

        private void GenerateTextMesh()
        {
            int textSize = sampleText.Length;
            int meshSize = textSize > 0 ? textSize : 1;

            Vector3[] vertices = new Vector3[meshSize * 4];
            int[] triangles = new int[meshSize * 6];
            Vector3[] normals = new Vector3[meshSize * 4];
            Vector2[] uvs = new Vector2[meshSize * 4];

            Vector2 origin = Vector2.zero;

            for (int i = 0; i < textSize; i++)
            {
                char @char = sampleText[i];
                Glyph glyph = _font[@char];
                GenerateGlyphMesh(glyph, i, ref origin, ref vertices, ref triangles, ref uvs);
                origin.x += (float)glyph.XAdvance;
            }

            for (int i = 0; i < meshSize * 4; i++)
            {
                normals[i] = Vector3.back;
            }

            Mesh mesh = new Mesh();
            mesh.vertices = vertices;
            mesh.triangles = triangles;
            mesh.normals = normals;
            mesh.uv = uvs;
            _mf.mesh = mesh;
        }

        private void GenerateGlyphMesh(Glyph glyph, int index, ref Vector2 origin, ref Vector3[] vertices, ref int[] triangles, ref Vector2[] uvs)
        {
            if (glyph == null)
                return;

            int i4 = index * 4;
            int i6 = index * 6;
            Vector2 o = new Vector2(origin.x + (float)glyph.XOffset, origin.y + (float)glyph.YOffset);

            vertices[i4 + 0] = new Vector3(o.x, o.y);
            vertices[i4 + 1] = new Vector3(o.x + (float)glyph.Width, o.y);
            vertices[i4 + 2] = new Vector3(o.x + (float)glyph.Width, o.y + (float)glyph.Height);
            vertices[i4 + 3] = new Vector3(o.x, o.y + (float)glyph.Height);

            triangles[i6 + 0] = i4 + 0;
            triangles[i6 + 1] = i4 + 2;
            triangles[i6 + 2] = i4 + 1;
            triangles[i6 + 3] = i4 + 0;
            triangles[i6 + 4] = i4 + 3;
            triangles[i6 + 5] = i4 + 2;

            uvs[i4 + 0] = new Vector2(glyph.UvMin.x, glyph.UvMin.y);
            uvs[i4 + 1] = new Vector2(glyph.UvMax.x, glyph.UvMin.y);
            uvs[i4 + 2] = new Vector2(glyph.UvMax.x, glyph.UvMax.y);
            uvs[i4 + 3] = new Vector2(glyph.UvMin.x, glyph.UvMax.y);
        }
    }
}
