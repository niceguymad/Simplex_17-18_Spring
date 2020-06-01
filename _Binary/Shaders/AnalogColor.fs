#version 330

in vec3 Color;
 
uniform vec3 SolidColor = vec3(-1,-1,-1);
uniform bool Complimentary = false;

out vec4 Fragment;

void main()
{
	vec3 output = Color;
	if(SolidColor.r != -1.0 && SolidColor.g != -1.0 && SolidColor.b != -1.0)
	{
		output = SolidColor;
	}
	
	if(Complimentary == true)
	{
		output = vec3(1.0f, 0.5f, 0.0f) - output;
	}
	
	Fragment = vec4(output,1);
		
	return;
}