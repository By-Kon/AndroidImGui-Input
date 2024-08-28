#ifndef 结构体
#define 结构体
#include <string>
struct Vec3 {
    float x, y, z;
};
class Vec2 {
public:
    float x;
    float y;

    Vec2() {
        this->x = 0;
        this->y = 0;
    }

    Vec2(float x, float y) {
        this->x = x;
        this->y = y;
    }

    static Vec2 Zero() {
        return Vec2(0.0f, 0.0f);
    }

    bool operator!=(const Vec2 &src) const {
        return (src.x != x) || (src.y != y);
    }

    Vec2 &operator+=(const Vec2 &v) {
        x += v.x;
        y += v.y;
        return *this;
    }

    Vec2 &operator-=(const Vec2 &v) {
        x -= v.x;
        y -= v.y;
        return *this;
    }
};


struct TextureInfo{
    ImTextureID textureId;
    int x;
    int y;
    int w;
    int h;
	
};


struct sESPMenu {
    bool 绘制;
    struct sPlayer {
        bool 骨骼=true;
        bool 方框=true;
        bool 物资;
        bool NPC=true;
		bool 手持=true;
        bool 帧率;
		bool 去除离线玩家;
		bool 预瞄=true;
        bool 射线=true;
        bool 血量=true;
        bool 世界;
        bool 名字=true;
        bool 距离=true;
        bool 载具=true;
		};
		sPlayer Player;
		struct sConfig {
            struct sRadar {
                int x;
                int y;
		        int w;
            };
            sRadar Radar;
    
            struct sVle {
                float x;
                float y;
            };
            sVle Vle;
        };
        sConfig Config;
	
		
};
sESPMenu ESPMenu;








#endif
