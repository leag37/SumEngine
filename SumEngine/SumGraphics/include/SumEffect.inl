//*************************************************************************************************
// Title: SumEffect.h
// Author: Gael Huber
// Description: Define a basic effect wrapper to group an effect and its variables.
//
// TODO: Switch over to use SumEngine data structures intead of STL
// TODO: Come up with a better way to store effect names -> probably from configuration
//*************************************************************************************************

// Basic Effect
//***********************************************
//SUMINLINE void BasicEffect::setWorldViewProj(const Matrix& m);
//SUMINLINE void BasicEffect::setWorld(const Matrix& m);
//SUMINLINE void BasicEffect::setWorldInvTranspose(const Matrix& m);
//SUMINLINE void BasicEffect::setTexTransform(const Matrix& m);
//SUMINLINE void BasicEffect::setEyePosW(const Float3& v);
//SUMINLINE void BasicEffect::setDirLights(const DirectionalLight* lights);
//SUMINLINE void BasicEffect::setMaterial(const Material& material);
//SUMINLINE void BasicEffect::setDiffuseMap(ID3D11ShaderResourceView* tex);

SUMINLINE ID3DX11EffectTechnique* BasicEffect::light1Tech()
{
	return _light1Tech;
}