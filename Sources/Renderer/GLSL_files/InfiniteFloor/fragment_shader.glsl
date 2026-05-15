#version 460

in vec3 NearP;
in vec3 FarP;

out vec4 frag_color;

// ОБЯЗАТЕЛЬНО: добавляем матрицы во фрагментный шейдер для расчета глубины
uniform mat4 u_Projection;
uniform mat4 u_View;

vec4 grid(vec3 fragPos3D, float scale){
    vec2 coord = fragPos3D.xz * scale;
    vec2 derivative = fwidth(coord);
    vec2 grid = abs(coord - floor(coord + 0.5)) / derivative;
    float line = min(grid.x, grid.y);

    vec4 color = vec4(0.0, 0.0, 0.0, 0.0); // Полностью прозрачный фон, чтобы видеть background
    if (line < 1.0) {
        color = vec4(0.8, 0.8, 0.8, 1.0); // Серые линии сетки
    }
    return color;
}

void main(){
    float t = -NearP.y / (FarP.y - NearP.y);
    if (t < 0.0) discard;
    
    vec3 fragPos3D = NearP + t * (FarP - NearP);

    // ---- МАГИЯ ИСПРАВЛЕНИЯ ГЛУБИНЫ ----
    // 1. Переводим 3D точку пересечения обратно в пространство экрана (Clip Space)
    vec4 projPos = u_Projection * u_View * vec4(fragPos3D, 1.0);
    
    // 2. Рассчитываем честную глубину Z от 0.0 до 1.0 и записываем в системный буфер
    gl_FragDepth = (projPos.z / projPos.w) * 0.5 + 0.5;
    // ----------------------------------

    frag_color = grid(fragPos3D, 1.0);
}
