#version 450 core

out vec4 fragColor;
in vec4 vColor;
in vec2 vTexCoords;
in flat float vTexIndex;

uniform sampler2D u_TextureUnit[32];

void main()
{
    int index = int(vTexIndex);
	switch(index)
    {
        case 0:  fragColor = vColor; break;
        case 1:  fragColor = texture(u_TextureUnit[1],  vTexCoords) * vColor; break;
        case 2:  fragColor = texture(u_TextureUnit[2],  vTexCoords) * vColor; break;
        case 3:  fragColor = texture(u_TextureUnit[3],  vTexCoords) * vColor; break;
        case 4:  fragColor = texture(u_TextureUnit[4],  vTexCoords) * vColor; break;
        case 5:  fragColor = texture(u_TextureUnit[5],  vTexCoords) * vColor; break;
        case 6:  fragColor = texture(u_TextureUnit[6],  vTexCoords) * vColor; break;
        case 7:  fragColor = texture(u_TextureUnit[7],  vTexCoords) * vColor; break;
        case 8:  fragColor = texture(u_TextureUnit[8],  vTexCoords) * vColor; break;
        case 9:  fragColor = texture(u_TextureUnit[9],  vTexCoords) * vColor; break;
        case 10: fragColor = texture(u_TextureUnit[10], vTexCoords) * vColor; break;
        case 11: fragColor = texture(u_TextureUnit[11], vTexCoords) * vColor; break;
        case 12: fragColor = texture(u_TextureUnit[12], vTexCoords) * vColor; break;
        case 13: fragColor = texture(u_TextureUnit[13], vTexCoords) * vColor; break;
        case 14: fragColor = texture(u_TextureUnit[14], vTexCoords) * vColor; break;
        case 15: fragColor = texture(u_TextureUnit[15], vTexCoords) * vColor; break;
        case 16: fragColor = texture(u_TextureUnit[16], vTexCoords) * vColor; break;
        case 17: fragColor = texture(u_TextureUnit[17], vTexCoords) * vColor; break;
        case 18: fragColor = texture(u_TextureUnit[18], vTexCoords) * vColor; break;
        case 19: fragColor = texture(u_TextureUnit[19], vTexCoords) * vColor; break;
        case 20: fragColor = texture(u_TextureUnit[20], vTexCoords) * vColor; break;
        case 21: fragColor = texture(u_TextureUnit[21], vTexCoords) * vColor; break;
        case 22: fragColor = texture(u_TextureUnit[22], vTexCoords) * vColor; break;
        case 23: fragColor = texture(u_TextureUnit[23], vTexCoords) * vColor; break;
        case 24: fragColor = texture(u_TextureUnit[24], vTexCoords) * vColor; break;
        case 25: fragColor = texture(u_TextureUnit[25], vTexCoords) * vColor; break;
        case 26: fragColor = texture(u_TextureUnit[26], vTexCoords) * vColor; break;
        case 27: fragColor = texture(u_TextureUnit[27], vTexCoords) * vColor; break;
        case 28: fragColor = texture(u_TextureUnit[28], vTexCoords) * vColor; break;
        case 29: fragColor = texture(u_TextureUnit[29], vTexCoords) * vColor; break;
        case 30: fragColor = texture(u_TextureUnit[30], vTexCoords) * vColor; break;
        case 31: fragColor = texture(u_TextureUnit[31], vTexCoords) * vColor; break;
    }
}