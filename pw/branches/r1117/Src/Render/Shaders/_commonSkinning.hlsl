#if SkeletalMeshPinValue == 1
float4x3 BonesMatrices[MAX_BONES] : register( BONES );

float4x3 MakeSkinnedMatrix(float4 weights, int4 idxs)
{
	float4x3 skinMatrix;

	int4 indices = 255 * idxs;

	skinMatrix  = weights[0] * BonesMatrices[ indices[0] ];
	skinMatrix += weights[1] * BonesMatrices[ indices[1] ];
	skinMatrix += weights[2] * BonesMatrices[ indices[2] ];
	skinMatrix += weights[3] * BonesMatrices[ indices[3] ];

	return skinMatrix;
}
#endif
