#type vertex
#version 450

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TextCord;
layout(location = 3) in float a_TexIndex;

uniform mat4 u_ViewProjection;

out vec2 v_TextCord;
out vec4 v_Color;
out flat float v_TexIndex;

void main()
{
	v_TextCord = a_TextCord;
	v_Color = a_Color;
	v_TexIndex = a_TexIndex;
	gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
}


#type fragment
#version 450
			
layout(location = 0) out vec4 color;

in vec2 v_TextCord;
in vec4 v_Color;
in flat float v_TexIndex;

uniform sampler2D u_Texture[32];
			
void main()
{
	int i = int(v_TexIndex);

	color = texture(u_Texture[i], v_TextCord) * v_Color;
}