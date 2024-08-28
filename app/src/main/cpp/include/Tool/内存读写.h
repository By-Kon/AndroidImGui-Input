#pragma once

#include <string>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <dirent.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/syscall.h>
#include <sys/mman.h>
#include <sys/uio.h>
#include <malloc.h>
#include <math.h>
#include <thread>
#include <iostream>
#include <sys/stat.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <iostream>
#include <locale>
#include <string>
#include <codecvt>
#include <dlfcn.h>

bool 载具飞天初始化;
long 自行车过滤;
long 自身地址;
int zshp;
long 指针3=0;
bool 跑;
long zs_z=0;
long 指针2 = 0;
long int 胸部地址=0;
long 坐标指针 = 0;
float 追踪距离限制 = 300.0f;
float 挥刀加速速度 =1.83f;
float 视角向前长度=3.0f;
float 水面高度高度=0.0f;
float 实体穿官强度=10.0f;
float 头部范围范围=2.0f;
float 视角向上长度=3.0f;
float 子弹速度速度=0.001f;
float 绘制距离限制=600.0f;
float 跑路速度速度=90.0f;
float 枪械射速射速=974138848;
float 自行车加速幅度=600.0f;
float 载具加速速度=90.0f;
const float 初始载具加速速度=90.0f;
const float 初始自行车加速幅度=600.0f;
const float 初始绘制距离限制=600.0f;
const float 初始枪械射速射速=974138848;
const float 初始头部范围范围=2.0f;
const float 初始跑路速度速度=90.0f;
const float 初始子弹速度速度=0.001f;
const float 初始视角向上长度=3.0f;
const float 初始挥刀加速速度 = 1.83f;
const float 初始实体穿官强度 = 10.0f;
const float 初始升降幅度 = 5.0f;
const float 初始遁地深度 = 1.94f;
const float 初始视角向前长度 = 3.0f;
const float 初始圈圈范围滑动条 = 600.0f;
const float 初始追踪距离限制 = 300.0f;
const float 初始水面高度高度 = 0.0f;
bool 载具加速;
bool 人物自瞄;
bool 防异常死;
bool 无视声音自行车;
bool 实体除树;
bool 子弹穿官;
bool 精准打击;
bool 初始化特殊功能2=true;
bool 一直挥刀;
bool 头部范围;
bool 无后防抖=true;
bool 强制建筑初始化=true;
bool 无视伤害npc=true;
bool 全图喝水;
bool 绿色名字;
bool 水下行走=true;
bool 实体除草=true;
bool 强制建筑;
bool 实体除建筑;
bool 视角向上;
bool 子弹速度;
bool 枪械据点;
bool 子弹追踪;
bool 绘制圈圈;
float 圈圈范围滑动条 = 600.0f;
float 升降幅度=5.0f;
float 遁地深度=1.94f;
bool 实体穿官;
bool 灵魂出窍;
bool 黄色名字;
bool 人物遁地;
bool 挥刀加速;
bool 机瞄十倍;
bool  昼夜交替;
bool 遁地防拉回;
bool 无视检测=true;
bool 时间定格;
bool 拳头卡武器;
bool 人物防摔;
bool 视角向前;
bool 子弹追踪1;
bool 重新获取包名和模块;
bool 枪械射速;
bool 无视接码=true;
long 载具_速;
long 载具_速1;
long 飞天_z;
long 飞天_防;
long 飞天_穿;
long 载具_z;
long 载具_x;
long 载具_y;
long 上车数据;
long 载具_防;
long 高跳_1,高跳_2,跳远_1;
int XA模块数据;
bool 上面按钮 = false;
bool 侧边按钮 = false;

int upButton = 50;
float upButtonabout = 0.47;

float SakRightSideWindow = 0.4;
// 按钮状态
static bool upButtonClicked[3] = { false, false, false };

// 声明静态变量来存储滑动条的值
static float verticalOffset = 0.5f;
static float horizontalOffset = 0.0f;
using namespace std;
uintptr_t Selfaddr,Gname, Uworld,Arrayaddr, Matrix, Objaddr, Object, Mesh, Human, Bone, Uleve,Players_add,NPC数组,视角地址,载具地址,载具数组,世界地址,物资地址,NPC地址,建筑地址,头部地址;
uintptr_t GNames;
uintptr_t GWorld;
uintptr_t Getmatrix;
typedef long ADDRESS;
typedef char PACKAGENAME;
typedef unsigned short UTF16;
typedef char UTF8;
float px,py;
long XA模块,libbase,libunityBss,libil2cppBss;
char lj[64];
int handle;
int isSize = 8;//默认32位
float matrix[16];
float MatrixValue[16] = { 0 };
int pid = { 0 };
#if defined(__arm__)
int process_vm_readv_syscall = 376;
int process_vm_writev_syscall = 377;
#elif defined(__aarch64__)
int process_vm_readv_syscall = 270;
int process_vm_writev_syscall = 271;
#elif defined(__i386__)
int process_vm_readv_syscall = 347;
int process_vm_writev_syscall = 348;
#else
int process_vm_readv_syscall = 310;
int process_vm_writev_syscall = 311;
#endif

ssize_t process_v(pid_t __pid, const struct iovec *__local_iov, unsigned long __local_iov_count,
				  const struct iovec *__remote_iov, unsigned long __remote_iov_count,
				  unsigned long __flags, bool iswrite)
{
	return syscall((iswrite ? process_vm_writev_syscall : process_vm_readv_syscall), __pid,
				   __local_iov, __local_iov_count, __remote_iov, __remote_iov_count, __flags);
}

bool WriteAddr(void *addr, void *buffer, size_t length) {
    unsigned long page_size = sysconf(_SC_PAGESIZE);
    unsigned long size = page_size * sizeof(uintptr_t);
    return mprotect((void *) ((uintptr_t) addr - ((uintptr_t) addr % page_size) - page_size), (size_t) size, PROT_EXEC | PROT_READ | PROT_WRITE) == 0 && memcpy(addr, buffer, length) != 0;
}

size_t pwritev(long address, void *buffer, size_t size)
{
	struct iovec iov_WriteBuffer, iov_WriteOffset;
	iov_WriteBuffer.iov_base = buffer;
	iov_WriteBuffer.iov_len = size;
	iov_WriteOffset.iov_base = (void *)address;
	iov_WriteOffset.iov_len = size;
	return syscall(SYS_process_vm_writev, pid, &iov_WriteBuffer, 1, &iov_WriteOffset, 1, 0);
}

// 进程读写内存
bool pvm(void *address, void *buffer, size_t size, bool iswrite)
{
	struct iovec local[1];
	struct iovec remote[1];
	local[0].iov_base = buffer;
	local[0].iov_len = size;
	remote[0].iov_base = address;
	remote[0].iov_len = size;
	ssize_t bytes = process_v(pid, local, 1, remote, 1, 0, iswrite);
	return bytes == size;
}

// 读取内存
bool vm_readv(long address, void *buffer, size_t size)
{
	return pvm(reinterpret_cast < void *>(address), buffer, size, false);
}

// 写入内存
bool vm_writev(long address, void *buffer, size_t size)
{
	return pvm(reinterpret_cast < void *>(address), buffer, size, true);
}

// 获取F类内存
float ReadFloat(long addr)
{
	float var = 0;
	vm_readv(addr, &var, isSize);
	return (var);
}

// 获取D类内存
int ReadDword(long addr)
{
	int var = 0;
	vm_readv(addr, &var, isSize);
	return (var);
}

// 获取指针
long ReadZZ(long addr)
{
	long var = 0;
	vm_readv(addr, &var, isSize);
	return (var);
}

float wrirteFloat(long address, float value)
{
	pwritev(address, &value, 4);
	return value;
}
int wrirteDword(long address, int value)
{
	pwritev(address, &value, 4);
	return value;
}

void writefloat(uintptr_t addr,float var){
WriteAddr(reinterpret_cast<void*>(addr),reinterpret_cast<void*>(&var),4);
}
void writedword(uintptr_t addr,int var){
WriteAddr(reinterpret_cast<void*>(addr),reinterpret_cast<void*>(&var),4);
}
// 获取基址
uintptr_t basea = 0;

long getModuleBase(const char *name, int index)
{
	int i = 0;
	long start = 0, end = 0;
	char line[1024] = { 0 };
	char fname[128];
	sprintf(fname, "/proc/%d/maps", pid);
	FILE *p = fopen(fname, "r");
	if (p)
	{
		while (fgets(line, sizeof(line), p))
		{
			if (strstr(line, name) != NULL)
			{
				i++;
				if (i == index)
				{
					sscanf(line, "%lx-%lx", &start, &end);
					break;
				}
			}
		}
		fclose(p);
	}
	return start;
}
// 写入F类内存


// 读取字符信息
void getUTF8(UTF8 * buf, long namepy)
{
    UTF16 buf16[16] = { 0 };
    vm_readv(namepy, buf16, 28);
    UTF16 *pTempUTF16 = buf16;
    UTF8 *pTempUTF8 = buf;
    UTF8 *pUTF8End = pTempUTF8 + 32;
    while (pTempUTF16 < pTempUTF16 + 28)
    {
        if (*pTempUTF16 <= 0x007F && pTempUTF8 + 1 < pUTF8End)
        {
            *pTempUTF8++ = (UTF8) * pTempUTF16;
        }
        else if (*pTempUTF16 >= 0x0080 && *pTempUTF16 <= 0x07FF && pTempUTF8 + 2 < pUTF8End)
        {
            *pTempUTF8++ = (*pTempUTF16 >> 6) | 0xC0;
            *pTempUTF8++ = (*pTempUTF16 & 0x3F) | 0x80;
        }
        else if (*pTempUTF16 >= 0x0800 && *pTempUTF16 <= 0xFFFF && pTempUTF8 + 3 < pUTF8End)
        {
            *pTempUTF8++ = (*pTempUTF16 >> 12) | 0xE0;
            *pTempUTF8++ = ((*pTempUTF16 >> 6) & 0x3F) | 0x80;
            *pTempUTF8++ = (*pTempUTF16 & 0x3F) | 0x80;
        }
        else
        {
            break;
        }
        pTempUTF16++;
    }
}

long int get_module_bss(int pid, const char *name)
{
	FILE *fp;
	int cnt = 0;
	long start;
	char tmp[256];
	fp = NULL;
	char line[1024];
	char fname[128];
	sprintf(fname, "/proc/%d/maps", pid);
	fp = fopen(fname, "r");
	while (!feof(fp))
	{
		fgets(tmp, 256, fp);
		if (cnt == 1)
		{
			if (strstr(tmp, "[anon:.bss]") != NULL)
			{
				sscanf(tmp, "%lx-%*lx", &start);
				break;
			}
			else
			{
				cnt = 0;
			}
		}
		if (strstr(tmp, name) != NULL)
		{
			cnt = 1;
		}
	}
	return start;
}

int readb(int &c, int num) {
  ++c;
  return num;
}

void MemoryWrite_FLOAT(float var, long long addr, int Size){
//WriteAddr(reinterpret_cast<void*>(addr),reinterpret_cast<void*>(&var),isSize);
vm_writev(addr, (void *)&var, Size);
}

template<typename S, typename ...s>
    S GetPointer(S addr, s... args) {
        int con   = 0;
        int arr[] = {(readb(con, args))...};
        S   add;
        add = ReadZZ(addr + arr[0]);
        for (int f = 1; f < con; f++) {
            if (f == con - 1) {
                add += arr[f];
                return add;
            }
            add = ReadZZ(add + arr[f]);
        }
        return add;
    }

// 定义圆周率
#define PI 3.141592653589793238

float camera, r_x, r_y, r_w;


struct D3DXVECTOR4
{
    float X;
    float Y;
    float Z;
    float W;
};

struct D3DVector
{
    float X;
    float Y;
    float Z;

    D3DVector()
    {
        this->X = 0;
        this->Y = 0;
        this->Z = 0;
    }

    D3DVector(float x, float y, float z)
    {
        this->X = x;
        this->Y = y;
        this->Z = z;
    }
};

struct FTransform
{
    D3DXVECTOR4 Rotation;
    D3DVector Translation;
    D3DVector Scale3D;
};

struct D3DXMATRIX
{
    float _11;
    float _12;
    float _13;
    float _14;
    float _21;
    float _22;
    float _23;
    float _24;
    float _31;
    float _32;
    float _33;
    float _34;
    float _41;
    float _42;
    float _43;
    float _44;
};

struct D2DVector
{
    float X;
    float Y;
};

float get2dDistance(float x, float y, float x1, float y1)
{
    float xx1 = x - x1;
    float yy2 = y - y1;
    // 取平方根
    return sqrt(xx1 * xx1 + yy2 * yy2);
}

float get_3D_Distance(float Self_x, float Self_y, float Self_z, float Object_x, float Object_y,
                      float Object_z)
{
    float x, y, z;
    x = Self_x - Object_x;
    y = Self_y - Object_y;
    z = Self_z - Object_z;
    // 求平方根
    return (float)(sqrt(x * x + y * y + z * z));
}

FTransform ReadFTransform(long location);
D3DXMATRIX ToMatrixWithScale(D3DXVECTOR4 Rotation, D3DVector Translation, D3DVector Scale3D);
D3DXMATRIX D3DXMatrixMultiply(D3DXMATRIX Pm1, D3DXMATRIX Pm2);
D2DVector rotateCoogetDword(float angle, float objectRadar_x, float objectRadar_y);
D3DVector D3dMatrixMultiply(D3DXMATRIX bonematrix, D3DXMATRIX actormatrix);
D3DVector getBoneXYZ(long humanAddr, long boneAddr, int Part);
D2DVector getBoneCoordinate(long humanAddr, long boneAddr, int Part);


D2DVector getPointingAngle(float object_x,
                           float object_y, float object_z, float Self_x, float Self_y,
                           float Self_z)
{
    D2DVector PointingAngle;
    float zbcx = object_x - Self_x;
    float zbcy = object_y - Self_y;
    float zbcz = object_z - Self_z;
    PointingAngle.X = atan2(zbcy, zbcx) * 180 / PI;
    PointingAngle.Y = atan2(zbcz, sqrt(zbcx * zbcx + zbcy * zbcy)) * 180 / PI;
    return PointingAngle;
}



// 获取骨骼2d
D2DVector getBoneCoordinate(long humanAddr, long boneAddr, int Part)
{
    D2DVector result;
    // 获取Bone数据
    FTransform Bone = ReadFTransform(boneAddr + Part * 48);
    // 获取Actor数据
    FTransform Actor = ReadFTransform(humanAddr);
    D3DXMATRIX Bone_Matrix = ToMatrixWithScale(Bone.Rotation, Bone.Translation, Bone.Scale3D);
    D3DXMATRIX Component_ToWorld_Matrix =
        ToMatrixWithScale(Actor.Rotation, Actor.Translation, Actor.Scale3D);
    D3DXMATRIX New_Matrix = D3DXMatrixMultiply(Bone_Matrix, Component_ToWorld_Matrix);
    float ViewW =
        matrix[3] * New_Matrix._41 + matrix[7] * New_Matrix._42 + matrix[11] * New_Matrix._43 +
        matrix[15];
    if (ViewW >= 0.01)
    {
        ViewW = 1 / ViewW;
        result.X =
            px + (matrix[0] * New_Matrix._41 + matrix[4] * New_Matrix._42 +
                  matrix[8] * New_Matrix._43 + matrix[12]) * ViewW * px;
        result.Y =
            py - (matrix[1] * New_Matrix._41 + matrix[5] * New_Matrix._42 +
                  matrix[9] * New_Matrix._43 + matrix[13]) * ViewW * py;
    }
    return result;
}


D3DVector getBoneXYZ(long humanAddr, long boneAddr, int Part)
{
    // 获取Bone数据
    FTransform Bone = ReadFTransform(boneAddr + Part * 48);
    // 获取Actor数据
    FTransform Actor = ReadFTransform(humanAddr);
    D3DXMATRIX Bone_Matrix = ToMatrixWithScale(Bone.Rotation, Bone.Translation, Bone.Scale3D);
    D3DXMATRIX Component_ToWorld_Matrix =
        ToMatrixWithScale(Actor.Rotation, Actor.Translation, Actor.Scale3D);
    D3DVector result = D3dMatrixMultiply(Bone_Matrix, Component_ToWorld_Matrix);
    return result;
}

FTransform ReadFTransform(long address)
{
    FTransform Result;
    Result.Rotation.X = ReadFloat(address);  // Rotation_X 
    Result.Rotation.Y = ReadFloat(address + 4);  // Rotation_y
    Result.Rotation.Z = ReadFloat(address + 8);  // Rotation_z
    Result.Rotation.W = ReadFloat(address + 12); // Rotation_w
    Result.Translation.X = ReadFloat(address + 16);  // /Translation_X
    Result.Translation.Y = ReadFloat(address + 20);  // Translation_y
    Result.Translation.Z = ReadFloat(address + 24);  // Translation_z
    Result.Scale3D.X = ReadFloat(address + 32);; // Scale_X
    Result.Scale3D.Y = ReadFloat(address + 36);; // Scale_y
    Result.Scale3D.Z = ReadFloat(address + 40);; // Scale_z
    return Result;
}

// 获取骨骼3d坐标
D3DVector D3dMatrixMultiply(D3DXMATRIX bonematrix, D3DXMATRIX actormatrix)
{
    D3DVector result;
    result.X =
        bonematrix._41 * actormatrix._11 + bonematrix._42 * actormatrix._21 +
        bonematrix._43 * actormatrix._31 + bonematrix._44 * actormatrix._41;
    result.Y =
        bonematrix._41 * actormatrix._12 + bonematrix._42 * actormatrix._22 +
        bonematrix._43 * actormatrix._32 + bonematrix._44 * actormatrix._42;
    result.Z =
        bonematrix._41 * actormatrix._13 + bonematrix._42 * actormatrix._23 +
        bonematrix._43 * actormatrix._33 + bonematrix._44 * actormatrix._43;
    return result;
}

// 计算旋转坐标
D2DVector rotateCoord(float angle, float objRadar_x, float objRadar_y)
{
    D2DVector radarCoordinate;
    float s = sin(angle * PI / 180);
    float c = cos(angle * PI / 180);
    radarCoordinate.X = objRadar_x * c + objRadar_y * s;
    radarCoordinate.Y = -objRadar_x * s + objRadar_y * c;
    return radarCoordinate;
}

float getDistanceToEnemy(float sx, float sy, float ex, float ey)
 {
    float dx = ex - sx;
    float dy = ey - sy;
    return sqrt(dx * dx + dy * dy);
 } 
 
D3DXMATRIX ToMatrixWithScale(D3DXVECTOR4 Rotation, D3DVector Translation, D3DVector Scale3D)
{
    D3DXMATRIX M;
    float X2, Y2, Z2, xX2, Yy2, Zz2, Zy2, Wx2, Xy2, Wz2, Zx2, Wy2;
    M._41 = Translation.X;
    M._42 = Translation.Y;
    M._43 = Translation.Z;
    X2 = Rotation.X + Rotation.X;
    Y2 = Rotation.Y + Rotation.Y;
    Z2 = Rotation.Z + Rotation.Z;
    xX2 = Rotation.X * X2;
    Yy2 = Rotation.Y * Y2;
    Zz2 = Rotation.Z * Z2;
    M._11 = (1 - (Yy2 + Zz2)) * Scale3D.X;
    M._22 = (1 - (xX2 + Zz2)) * Scale3D.Y;
    M._33 = (1 - (xX2 + Yy2)) * Scale3D.Z;
    Zy2 = Rotation.Y * Z2;
    Wx2 = Rotation.W * X2;
    M._32 = (Zy2 - Wx2) * Scale3D.Z;
    M._23 = (Zy2 + Wx2) * Scale3D.Y;
    Xy2 = Rotation.X * Y2;
    Wz2 = Rotation.W * Z2;
    M._21 = (Xy2 - Wz2) * Scale3D.Y;
    M._12 = (Xy2 + Wz2) * Scale3D.X;
    Zx2 = Rotation.X * Z2;
    Wy2 = Rotation.W * Y2;
    M._31 = (Zx2 + Wy2) * Scale3D.Z;
    M._13 = (Zx2 - Wy2) * Scale3D.X;
    M._14 = 0;
    M._24 = 0;
    M._34 = 0;
    M._44 = 1;
    return M;
}

D3DXMATRIX D3DXMatrixMultiply(D3DXMATRIX Pm1, D3DXMATRIX Pm2)
{
    D3DXMATRIX Pout;
    Pout._11 = Pm1._11 * Pm2._11 + Pm1._12 * Pm2._21 + Pm1._13 * Pm2._31 + Pm1._14 * Pm2._41;
    Pout._12 = Pm1._11 * Pm2._12 + Pm1._12 * Pm2._22 + Pm1._13 * Pm2._32 + Pm1._14 * Pm2._42;
    Pout._13 = Pm1._11 * Pm2._13 + Pm1._12 * Pm2._23 + Pm1._13 * Pm2._33 + Pm1._14 * Pm2._43;
    Pout._14 = Pm1._11 * Pm2._14 + Pm1._12 * Pm2._24 + Pm1._13 * Pm2._34 + Pm1._14 * Pm2._44;
    Pout._21 = Pm1._21 * Pm2._11 + Pm1._22 * Pm2._21 + Pm1._23 * Pm2._31 + Pm1._24 * Pm2._41;
    Pout._22 = Pm1._21 * Pm2._12 + Pm1._22 * Pm2._22 + Pm1._23 * Pm2._32 + Pm1._24 * Pm2._42;
    Pout._23 = Pm1._21 * Pm2._13 + Pm1._22 * Pm2._23 + Pm1._23 * Pm2._33 + Pm1._24 * Pm2._43;
    Pout._24 = Pm1._21 * Pm2._14 + Pm1._22 * Pm2._24 + Pm1._23 * Pm2._34 + Pm1._24 * Pm2._44;
    Pout._31 = Pm1._31 * Pm2._11 + Pm1._32 * Pm2._21 + Pm1._33 * Pm2._31 + Pm1._34 * Pm2._41;
    Pout._32 = Pm1._31 * Pm2._12 + Pm1._32 * Pm2._22 + Pm1._33 * Pm2._32 + Pm1._34 * Pm2._42;
    Pout._33 = Pm1._31 * Pm2._13 + Pm1._32 * Pm2._23 + Pm1._33 * Pm2._33 + Pm1._34 * Pm2._43;
    Pout._34 = Pm1._31 * Pm2._14 + Pm1._32 * Pm2._24 + Pm1._33 * Pm2._34 + Pm1._34 * Pm2._44;
    Pout._41 = Pm1._41 * Pm2._11 + Pm1._42 * Pm2._21 + Pm1._43 * Pm2._31 + Pm1._44 * Pm2._41;
    Pout._42 = Pm1._41 * Pm2._12 + Pm1._42 * Pm2._22 + Pm1._43 * Pm2._32 + Pm1._44 * Pm2._42;
    Pout._43 = Pm1._41 * Pm2._13 + Pm1._42 * Pm2._23 + Pm1._43 * Pm2._33 + Pm1._44 * Pm2._43;
    Pout._44 = Pm1._41 * Pm2._14 + Pm1._42 * Pm2._24 + Pm1._43 * Pm2._34 + Pm1._44 * Pm2._44;
    return Pout;
}

char* getClassName(uintptr_t ObjectAddress){
    
    int oid = ReadDword(ObjectAddress + 0x10);
    uintptr_t ye = ReadZZ(Gname + (oid / 0x4000) * 0x4);
    uintptr_t xu = ReadZZ(ye + (oid % 0x4000) * 0x4);
    //static 类型的内部变量一直占据存储空间的变量。 函数调用完毕不会弹出栈
    static char Item[256];
    vm_readv(xu + 0x8, Item, sizeof(Item));
    return Item;
}

// 获取基址
unsigned int get_module_base(int pid, const char *module_name)
{
	FILE *fp;
	long addr = 0;
	char *pch;
	char filename[64];
	char line[1024];
	snprintf(filename, sizeof(filename), "/proc/%d/maps", pid);
	fp = fopen(filename, "r");
	if (fp != NULL)
	{
		while (fgets(line, sizeof(line), fp))
		{
			if (strstr(line, module_name))
			{
				pch = strtok(line, "-");
				addr = strtoul(pch, NULL, 16);
				if (addr == 0x8000)
					addr = 0;
				break;
			}
		}
		fclose(fp);
	}
	return addr;
}



int getProcessID(const char *packageName)
{
    int id = -1;
    DIR *dir;
    FILE *fp;
    char filename[64];
    char cmdline[64];
    struct dirent *entry;
    dir = opendir("/proc");
    while ((entry = readdir(dir)) != NULL)
    {
        id = atoi(entry->d_name);
        if (id != 0)
        {
            sprintf(filename, "/proc/%d/cmdline", id);
            fp = fopen(filename, "r");
            if (fp)
            {
                fgets(cmdline, sizeof(cmdline), fp);
                fclose(fp);
                if (strcmp(packageName, cmdline) == 0)
                {
                    return id;
                }
            }
        }
    }
    closedir(dir);
    return -1;
}


float Xawritefloat(int pid,long addr,float value)    //XA修改
{
	char lj[64];
	int handle;
	sprintf(lj, "/proc/%d/mem", pid);
	handle = open(lj, O_RDWR);
	lseek(handle, 0, SEEK_SET);
	pwrite(handle, &value, 4, addr);
	close(handle);
	return 0;
}

float Xawritedword(int pid,long addr,long int value)    //XA修改
{
	char lj[64];
	int handle;
	sprintf(lj, "/proc/%d/mem", pid);
	handle = open(lj, O_RDWR);
	lseek(handle, 0, SEEK_SET);
	pwrite(handle, &value, 4, addr);
	close(handle);
	return 0;
}

