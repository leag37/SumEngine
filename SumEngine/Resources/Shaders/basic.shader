// Title: basic.shader
// Author: Gael Huber
// Description: Config for a basic shader, configured for HLSL

// Definition for shader programs
vertex_shader basic_vs
{
	shader_model hlsl
	{
		source basic.hlsl
		target vs_5_0
		entry_point basic_vs
	}
}

pixel_shader basic_ps
{
	shader_model hlsl
	{
		source basic.hlsl
		target vs_5_0
		entry_point basic_ps
	}
}