#pragma region decs_defs
#if defined(__GNUC__)
typedef          long long ll;
typedef unsigned long long ull;
#define __int64 long long
#define __int32 int
#define __int16 short
#define __int8  char
#define MAKELL(num) num ## LL
#define FMT_64 "ll"
#elif defined(_MSC_VER)
typedef          __int64 ll;
typedef unsigned __int64 ull;
#define MAKELL(num) num ## i64
#define FMT_64 "I64"
#elif defined (__BORLANDC__)
typedef          __int64 ll;
typedef unsigned __int64 ull;
#define MAKELL(num) num ## i64
#define FMT_64 "L"
#else
#error "unknown compiler"
#endif
typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned short ushort;
//typedef unsigned long ulong;

typedef          char   int8;
typedef   signed char   sint8;
typedef unsigned char   uint8;
typedef          short  int16;
typedef   signed short  sint16;
typedef unsigned short  uint16;
typedef          int    int32;
typedef   signed int    sint32;
typedef unsigned int    uint32;
typedef ll              int64;
typedef ll              sint64;
typedef ull             uint64;

// Partially defined types:
#define _BYTE  uint8
#define _WORD  uint16
#define _DWORD uint32
#define _QWORD uint64
#if !defined(_MSC_VER)
#define _LONGLONG __int128
#endif

#ifndef _WINDOWS_
typedef int8 BYTE;
typedef int16 WORD;
typedef int32 DWORD;
typedef int32 LONG;
#endif
typedef int64 QWORD;
#ifndef __cplusplus
typedef int bool;       // we want to use bool in our C programs
#endif

						// Some convenience macros to make partial accesses nicer
						// first unsigned macros:
#define LOBYTE(x)   (*((_BYTE*)&(x)))   // low byte
#define LOWORD(x)   (*((_WORD*)&(x)))   // low word
#define LODWORD(x)  (*((_DWORD*)&(x)))  // low dword
#define HIBYTE(x)   (*((_BYTE*)&(x)+1))
#define HIWORD(x)   (*((_WORD*)&(x)+1))
#define HIDWORD(x)  (*((_DWORD*)&(x)+1))
#define BYTEn(x, n)   (*((_BYTE*)&(x)+n))
#define WORDn(x, n)   (*((_WORD*)&(x)+n))
#define BYTE1(x)   BYTEn(x,  1)         // byte 1 (counting from 0)
#define BYTE2(x)   BYTEn(x,  2)
#define BYTE3(x)   BYTEn(x,  3)
#define BYTE4(x)   BYTEn(x,  4)
#define BYTE5(x)   BYTEn(x,  5)
#define BYTE6(x)   BYTEn(x,  6)
#define BYTE7(x)   BYTEn(x,  7)
#define BYTE8(x)   BYTEn(x,  8)
#define BYTE9(x)   BYTEn(x,  9)
#define BYTE10(x)  BYTEn(x, 10)
#define BYTE11(x)  BYTEn(x, 11)
#define BYTE12(x)  BYTEn(x, 12)
#define BYTE13(x)  BYTEn(x, 13)
#define BYTE14(x)  BYTEn(x, 14)
#define BYTE15(x)  BYTEn(x, 15)
#define WORD1(x)   WORDn(x,  1)
#define WORD2(x)   WORDn(x,  2)         // third word of the object, unsigned
#define WORD3(x)   WORDn(x,  3)
#define WORD4(x)   WORDn(x,  4)
#define WORD5(x)   WORDn(x,  5)
#define WORD6(x)   WORDn(x,  6)
#define WORD7(x)   WORDn(x,  7)

						// now signed macros (the same but with sign extension)
#define SLOBYTE(x)   (*((int8*)&(x)))
#define SLOWORD(x)   (*((int16*)&(x)))
#define SLODWORD(x)  (*((int32*)&(x)))
#define SHIBYTE(x)   (*((int8*)&(x)+1))
#define SHIWORD(x)   (*((int16*)&(x)+1))
#define SHIDWORD(x)  (*((int32*)&(x)+1))
#define SBYTEn(x, n)   (*((int8*)&(x)+n))
#define SWORDn(x, n)   (*((int16*)&(x)+n))
#define SBYTE1(x)   SBYTEn(x,  1)
#define SBYTE2(x)   SBYTEn(x,  2)
#define SBYTE3(x)   SBYTEn(x,  3)
#define SBYTE4(x)   SBYTEn(x,  4)
#define SBYTE5(x)   SBYTEn(x,  5)
#define SBYTE6(x)   SBYTEn(x,  6)
#define SBYTE7(x)   SBYTEn(x,  7)
#define SBYTE8(x)   SBYTEn(x,  8)
#define SBYTE9(x)   SBYTEn(x,  9)
#define SBYTE10(x)  SBYTEn(x, 10)
#define SBYTE11(x)  SBYTEn(x, 11)
#define SBYTE12(x)  SBYTEn(x, 12)
#define SBYTE13(x)  SBYTEn(x, 13)
#define SBYTE14(x)  SBYTEn(x, 14)
#define SBYTE15(x)  SBYTEn(x, 15)
#define SWORD1(x)   SWORDn(x,  1)
#define SWORD2(x)   SWORDn(x,  2)
#define SWORD3(x)   SWORDn(x,  3)
#define SWORD4(x)   SWORDn(x,  4)
#define SWORD5(x)   SWORDn(x,  5)
#define SWORD6(x)   SWORDn(x,  6)
#define SWORD7(x)   SWORDn(x,  7)


						// Helper functions to represent some assembly instructions.

#ifdef __cplusplus

						// Fill memory block with an integer value
inline void memset32(void* ptr, uint32 value, int count)
{
	uint32* p = (uint32*)ptr;
	for (int i = 0; i < count; i++)
		*p++ = value;
}

// Generate a reference to pair of operands
template<class T>  int16 __PAIR__(int8  high, T low) { return (((int16)high) << sizeof(high) * 8) | uint8(low); }
template<class T>  int32 __PAIR__(int16 high, T low) { return (((int32)high) << sizeof(high) * 8) | uint16(low); }
template<class T>  int64 __PAIR__(int32 high, T low) { return (((int64)high) << sizeof(high) * 8) | uint32(low); }
template<class T> uint16 __PAIR__(uint8  high, T low) { return (((uint16)high) << sizeof(high) * 8) | uint8(low); }
template<class T> uint32 __PAIR__(uint16 high, T low) { return (((uint32)high) << sizeof(high) * 8) | uint16(low); }
template<class T> uint64 __PAIR__(uint32 high, T low) { return (((uint64)high) << sizeof(high) * 8) | uint32(low); }

// rotate left
template<class T> T __ROL__(T value, uint count)
{
	const uint nbits = sizeof(T) * 8;
	count %= nbits;

	T high = value >> (nbits - count);
	value <<= count;
	value |= high;
	return value;
}

// rotate right
template<class T> T __ROR__(T value, uint count)
{
	const uint nbits = sizeof(T) * 8;
	count %= nbits;

	T low = value << (nbits - count);
	value >>= count;
	value |= low;
	return value;
}

// carry flag of left shift
template<class T> int8 __MKCSHL__(T value, uint count)
{
	const uint nbits = sizeof(T) * 8;
	count %= nbits;

	return (value >> (nbits - count)) & 1;
}

// carry flag of right shift
template<class T> int8 __MKCSHR__(T value, uint count)
{
	return (value >> (count - 1)) & 1;
}

// sign flag
template<class T> int8 __SETS__(T x)
{
	if (sizeof(T) == 1)
		return int8(x) < 0;
	if (sizeof(T) == 2)
		return int16(x) < 0;
	if (sizeof(T) == 4)
		return int32(x) < 0;
	return int64(x) < 0;
}

// overflow flag of subtraction (x-y)
template<class T, class U> int8 __OFSUB__(T x, U y)
{
	if (sizeof(T) < sizeof(U))
	{
		U x2 = x;
		int8 sx = __SETS__(x2);
		return (sx ^ __SETS__(y)) & (sx ^ __SETS__(x2 - y));
	}
	else
	{
		T y2 = y;
		int8 sx = __SETS__(x);
		return (sx ^ __SETS__(y2)) & (sx ^ __SETS__(x - y2));
	}
}

// overflow flag of addition (x+y)
template<class T, class U> int8 __OFADD__(T x, U y)
{
	if (sizeof(T) < sizeof(U))
	{
		U x2 = x;
		int8 sx = __SETS__(x2);
		return ((1 ^ sx) ^ __SETS__(y)) & (sx ^ __SETS__(x2 + y));
	}
	else
	{
		T y2 = y;
		int8 sx = __SETS__(x);
		return ((1 ^ sx) ^ __SETS__(y2)) & (sx ^ __SETS__(x + y2));
	}
}

// carry flag of subtraction (x-y)
template<class T, class U> int8 __CFSUB__(T x, U y)
{
	int size = sizeof(T) > sizeof(U) ? sizeof(T) : sizeof(U);
	if (size == 1)
		return uint8(x) < uint8(y);
	if (size == 2)
		return uint16(x) < uint16(y);
	if (size == 4)
		return uint32(x) < uint32(y);
	return uint64(x) < uint64(y);
}

// carry flag of addition (x+y)
template<class T, class U> int8 __CFADD__(T x, U y)
{
	int size = sizeof(T) > sizeof(U) ? sizeof(T) : sizeof(U);
	if (size == 1)
		return uint8(x) > uint8(x + y);
	if (size == 2)
		return uint16(x) > uint16(x + y);
	if (size == 4)
		return uint32(x) > uint32(x + y);
	return uint64(x) > uint64(x + y);
}

#else
						// The following definition is not quite correct because it always returns
						// uint64. The above C++ functions are good, though.
#define __PAIR__(high, low) (((uint64)(high)<<sizeof(high)*8) | low)
						// For C, we just provide macros, they are not quite correct.
#define __ROL__(x, y) __rotl__(x, y)      // Rotate left
#define __ROR__(x, y) __rotr__(x, y)      // Rotate right
#define __CFSHL__(x, y) invalid_operation // Generate carry flag for (x<<y)
#define __CFSHR__(x, y) invalid_operation // Generate carry flag for (x>>y)
#define __CFADD__(x, y) invalid_operation // Generate carry flag for (x+y)
#define __CFSUB__(x, y) invalid_operation // Generate carry flag for (x-y)
#define __OFADD__(x, y) invalid_operation // Generate overflow flag for (x+y)
#define __OFSUB__(x, y) invalid_operation // Generate overflow flag for (x-y)
#endif

						// No definition for rcl/rcr because the carry flag is unknown
#define __RCL__(x, y)    invalid_operation // Rotate left thru carry
#define __RCR__(x, y)    invalid_operation // Rotate right thru carry
#define __MKCRCL__(x, y) invalid_operation // Generate carry flag for a RCL
#define __MKCRCR__(x, y) invalid_operation // Generate carry flag for a RCR
#define __SETP__(x, y)   invalid_operation // Generate parity flag for (x-y)

						// In the decompilation listing there are some objects declarared as _UNKNOWN
						// because we could not determine their types. Since the C compiler does not
						// accept void item declarations, we replace them by anything of our choice,
						// for example a char:

#define _UNKNOWN char
struct uint128_t {
	uint64_t low;
	uint64_t high;
};
static uint8_t rol1(uint8_t x, unsigned int count) {
	count %= 8;
	return (x << count) | (x >> (8 - count));
}
static uint16_t __ROL2__(uint16_t x, unsigned int count) {
	count %= 16;
	return (x << count) | (x >> (16 - count));
}
static uint32_t __ROL4__(uint32_t x, unsigned int count) {
	count %= 32;
	return (x << count) | (x >> (32 - count));
}
static uint64_t rol8(uint64_t x, unsigned int count) {
	count %= 64;
	return (x << count) | (x >> (64 - count));
}
static uint8_t ror1(uint8_t x, unsigned int count) {
	count %= 8;
	return (x << (8 - count)) | (x >> count);
}
static uint16_t __ROR2__(uint16_t x, unsigned int count) {
	count %= 16;
	return (x << (16 - count)) | (x >> count);
}
static uint32_t __ROR4__(uint32_t x, unsigned int count) {
	count %= 32;
	return (x << (32 - count)) | (x >> count);
}
static uint64_t ror8(uint64_t x, unsigned int count) {
	count %= 64;
	return (x << (64 - count)) | (x >> count);
}
#ifdef _MSC_VER
#define snprintf _snprintf
#define vsnprintf _vsnprintf
#endif
#pragma endregion

struct FQuat
{
	float x;
	float y;
	float z;
	float w;
};


struct FTransform
{
	FQuat rot;
	D3DXVECTOR3 translation;
	char pad[4];
	D3DXVECTOR3 scale;
	char pad1[4];
	D3DMATRIX ToMatrixWithScale()
	{
		D3DMATRIX m;
		m._41 = translation.x;
		m._42 = translation.y;
		m._43 = translation.z;

		float x2 = rot.x + rot.x;
		float y2 = rot.y + rot.y;
		float z2 = rot.z + rot.z;

		float xx2 = rot.x * x2;
		float yy2 = rot.y * y2;
		float zz2 = rot.z * z2;
		m._11 = (1.0f - (yy2 + zz2)) * scale.x;
		m._22 = (1.0f - (xx2 + zz2)) * scale.y;
		m._33 = (1.0f - (xx2 + yy2)) * scale.z;

		float yz2 = rot.y * z2;
		float wx2 = rot.w * x2;
		m._32 = (yz2 - wx2) * scale.z;
		m._23 = (yz2 + wx2) * scale.y;

		float xy2 = rot.x * y2;
		float wz2 = rot.w * z2;
		m._21 = (xy2 - wz2) * scale.y;
		m._12 = (xy2 + wz2) * scale.x;

		float xz2 = rot.x * z2;
		float wy2 = rot.w * y2;
		m._31 = (xz2 + wy2) * scale.z;
		m._13 = (xz2 - wy2) * scale.x;

		m._14 = 0.0f;
		m._24 = 0.0f;
		m._34 = 0.0f;
		m._44 = 1.0f;

		return m;
	}
};

D3DMATRIX MatrixMultiplication(D3DMATRIX pM1, D3DMATRIX pM2)
{
	D3DMATRIX pOut;
	pOut._11 = pM1._11 * pM2._11 + pM1._12 * pM2._21 + pM1._13 * pM2._31 + pM1._14 * pM2._41;
	pOut._12 = pM1._11 * pM2._12 + pM1._12 * pM2._22 + pM1._13 * pM2._32 + pM1._14 * pM2._42;
	pOut._13 = pM1._11 * pM2._13 + pM1._12 * pM2._23 + pM1._13 * pM2._33 + pM1._14 * pM2._43;
	pOut._14 = pM1._11 * pM2._14 + pM1._12 * pM2._24 + pM1._13 * pM2._34 + pM1._14 * pM2._44;
	pOut._21 = pM1._21 * pM2._11 + pM1._22 * pM2._21 + pM1._23 * pM2._31 + pM1._24 * pM2._41;
	pOut._22 = pM1._21 * pM2._12 + pM1._22 * pM2._22 + pM1._23 * pM2._32 + pM1._24 * pM2._42;
	pOut._23 = pM1._21 * pM2._13 + pM1._22 * pM2._23 + pM1._23 * pM2._33 + pM1._24 * pM2._43;
	pOut._24 = pM1._21 * pM2._14 + pM1._22 * pM2._24 + pM1._23 * pM2._34 + pM1._24 * pM2._44;
	pOut._31 = pM1._31 * pM2._11 + pM1._32 * pM2._21 + pM1._33 * pM2._31 + pM1._34 * pM2._41;
	pOut._32 = pM1._31 * pM2._12 + pM1._32 * pM2._22 + pM1._33 * pM2._32 + pM1._34 * pM2._42;
	pOut._33 = pM1._31 * pM2._13 + pM1._32 * pM2._23 + pM1._33 * pM2._33 + pM1._34 * pM2._43;
	pOut._34 = pM1._31 * pM2._14 + pM1._32 * pM2._24 + pM1._33 * pM2._34 + pM1._34 * pM2._44;
	pOut._41 = pM1._41 * pM2._11 + pM1._42 * pM2._21 + pM1._43 * pM2._31 + pM1._44 * pM2._41;
	pOut._42 = pM1._41 * pM2._12 + pM1._42 * pM2._22 + pM1._43 * pM2._32 + pM1._44 * pM2._42;
	pOut._43 = pM1._41 * pM2._13 + pM1._42 * pM2._23 + pM1._43 * pM2._33 + pM1._44 * pM2._43;
	pOut._44 = pM1._41 * pM2._14 + pM1._42 * pM2._24 + pM1._43 * pM2._34 + pM1._44 * pM2._44;

	return pOut;
}


enum eBone
{
	BONE_NULL_1 = 0,
	BONE_NULL_2 = 1,
	BONE_PELVIS_1 = 2,
	BONE_PELVIS_2 = 3,
	BONE_PELVIS_3 = 4,
	BONE_TORSO = 5,

	BONE_CHEST_LOW = 6,
	BONE_CHEST = 7,

	// -------------------------

	BONE_CHEST_LEFT = 8,

	BONE_L_SHOULDER_1 = 9,
	BONE_L_ELBOW = 10,

	BONE_L_HAND_ROOT_1 = 11,

	BONE_L_FINGER_1_ROOT = 12,
	BONE_L_FINGER_1_LOW = 13,
	BONE_L_FINGER_1 = 14,
	BONE_L_FINGER_1_TOP = 15,

	BONE_L_FINGER_2_ROOT = 16,
	BONE_L_FINGER_2_LOW = 17,
	BONE_L_FINGER_2 = 18,
	BONE_L_FINGER_2_TOP = 19,

	BONE_L_FINGER_3_ROOT = 20,
	BONE_L_FINGER_3_LOW = 21,
	BONE_L_FINGER_3 = 22,
	BONE_L_FINGER_3_TOP = 23,

	BONE_L_FINGER_4_ROOT = 24,
	BONE_L_FINGER_4_LOW = 25,
	BONE_L_FINGER_4_ = 26,
	BONE_L_FINGER_4_TOP = 27,

	BONE_L_THUMB_ROOT = 28,
	BONE_L_THUMB_LOW = 29,
	BONE_L_THUMB = 30,

	BONE_L_HAND_ROOT_2 = 31,
	BONE_L_WRIST = 32,
	BONE_L_ARM_LOWER = 33,

	BONE_L_SHOULDER_2 = 34,

	BONE_L_ARM_TOP = 35,

	// -------------------------

	BONE_CHEST_TOP_1 = 36,

	// -------------------------

	BONE_CHEST_RIGHT = 37,

	BONE_R_ELBOW = 38,

	BONE_R_HAND_ROOT_1 = 39,

	BONE_R_FINGER_1_ROOT = 40,
	BONE_R_FINGER_1_LOW = 41,
	BONE_R_FINGER_1 = 42,
	BONE_R_FINGER_1_TOP = 43,

	BONE_R_FINGER_2_ROOT = 44,
	BONE_R_FINGER_2_LOW = 45,
	BONE_R_FINGER_2 = 46,
	BONE_R_FINGER_2_TOP = 47,

	BONE_R_FINGER_3_ROOT = 48,
	BONE_R_FINGER_3_LOW = 49,
	BONE_R_FINGER_3 = 50,
	BONE_R_FINGER_3_TOP = 51,

	BONE_R_FINGER_4_ROOT = 52,
	BONE_R_FINGER_4_LOW = 53,
	BONE_R_FINGER_4_ = 54,
	BONE_R_FINGER_4_TOP = 55,

	BONE_R_THUMB_ROOT = 56,
	BONE_R_THUMB_LOW = 57,
	BONE_R_THUMB = 58,

	BONE_R_HAND_ROOT = 59,
	BONE_R_WRIST = 60,
	BONE_R_ARM_LOWER = 61,

	BONE_R_SHOULDER = 62,

	BONE_R_ARM_TOP = 63,

	// -------------------------

	BONE_CHEST_TOP_2 = 64,

	BONE_NECK = 65,
	BONE_HEAD = 66,

	// -------------------------

	BONE_L_LEG_ROOT = 67,
	BONE_L_KNEE = 68,
	BONE_L_FOOT_ROOT = 69,
	BONE_L_SHIN = 70,
	BONE_L_FOOT_MID = 71,
	BONE_L_FOOT_LOW = 72,
	BONE_L_THIGH = 73,

	// -------------------------

	BONE_R_LEG_ROOT = 74,
	BONE_R_KNEE = 75,
	BONE_R_FOOT_ROOT = 76,
	BONE_R_SHIN = 77,
	BONE_R_FOOT_MID = 78,
	BONE_R_FOOT_LOW = 79,
	BONE_R_THIGH = 80,

	// -------------------------

	BONE_NULL_3 = 81,
	BONE_MISC_L_FOOT = 82,
	BONE_MISC_R_FOOT = 83,
	BONE_NULL_4 = 84,
	BONE_MISC_R_HAND_1 = 85,
	BONE_MISC_L_HAND = 86,
	BONE_MISC_R_HAND_2 = 87,
};

class FMinimalViewInfo // CameraManager + 0x1260
{
public:
	D3DXVECTOR3 Loc; //+ 0x1260
	D3DXVECTOR3 Rot; //+ 0x126C
	float FOV;     //+ 0x1278
};


class FRotator
{
public:
	float pitch, yaw, roll;

	FRotator() : pitch(0.0f), yaw(0.0f), roll(0.0f) {}
	FRotator(float _pitch, float _yaw, float _roll)
	{
		pitch = _pitch;
		yaw = _yaw;
		roll = _roll;
	}

	FRotator(const D3DXVECTOR3& vec)
	{
		static constexpr auto RADPI = static_cast<float>(180 / 3.14159265358979323846);
		yaw = static_cast<float>(atan2(vec.y, vec.x)) * RADPI;
		pitch = static_cast<float>(atan2(vec.z, sqrt((vec.x * vec.x) + (vec.y * vec.y)))) * RADPI;
		roll = 0;
	}

	FLOAT length() const
	{
		return abs(sqrt(pitch * pitch + yaw * yaw + roll * roll));
	}

	void Clamp()
	{
		auto result = *this;
		if (result.pitch > 180)
			result.pitch -= 360;

		else if (result.pitch < -180)
			result.pitch += 360;

		if (result.yaw > 180)
			result.yaw -= 360;

		else if (result.yaw < -180)
			result.yaw += 360;

		if (result.pitch < -89)
			result.pitch = -89;

		if (result.pitch > 89)
			result.pitch = 89;

		while (result.yaw < -180.0f)
			result.yaw += 360.0f;

		while (result.yaw > 180.0f)
			result.yaw -= 360.0f;

		result.roll = 0;
		return;
	}

	void get_axes(D3DXVECTOR3& x, D3DXVECTOR3& y, D3DXVECTOR3& z) const
	{
		auto m = to_matrix();

		x = D3DXVECTOR3(m._11, m._12, m._13);
		y = D3DXVECTOR3(m._21, m._22, m._23);
		z = D3DXVECTOR3(m._31, m._32, m._33);
	}

	D3DMATRIX to_matrix(const D3DXVECTOR3& origin = { 0.0f, 0.0f, 0.0f }) const
	{
		auto radPitch = static_cast<float>(pitch * 3.14159265358979323846 / 180.f);
		auto radYaw = static_cast<float>(yaw * 3.14159265358979323846 / 180.f);
		auto radRoll = static_cast<float>(roll * 3.14159265358979323846 / 180.f);

		auto SP = static_cast<float>(sin(radPitch));
		auto CP = static_cast<float>(cos(radPitch));
		auto SY = static_cast<float>(sin(radYaw));
		auto CY = static_cast<float>(cos(radYaw));
		auto SR = static_cast<float>(sin(radRoll));
		auto CR = static_cast<float>(cos(radRoll));

		D3DMATRIX m;

		m.m[0][0] = CP * CY;
		m.m[0][1] = CP * SY;
		m.m[0][2] = SP;
		m.m[0][3] = 0.f;

		m.m[1][0] = SR * SP * CY - CR * SY;
		m.m[1][1] = SR * SP * SY + CR * CY;
		m.m[1][2] = -SR * CP;
		m.m[1][3] = 0.f;

		m.m[2][0] = -(CR * SP * CY + SR * SY);
		m.m[2][1] = CY * SR - CR * SP * SY;
		m.m[2][2] = CR * CP;
		m.m[2][3] = 0.f;

		m.m[3][0] = origin.x;
		m.m[3][1] = origin.y;
		m.m[3][2] = origin.z;
		m.m[3][3] = 1.f;
		return m;
	}

	bool operator ==(const FRotator& o) const
	{
		return pitch == o.pitch && yaw == o.yaw && roll == o.roll;
	}

	bool operator !=(const FRotator& o) const
	{
		return !(*this == o);
	}

	FRotator& operator+(const FRotator& o)
	{
		pitch += o.pitch;
		yaw += o.yaw;
		roll += o.roll;
		return *this;
	}
	FRotator& operator-(const FRotator& o)
	{
		pitch -= o.pitch;
		yaw -= o.yaw;
		roll -= o.roll;
		return *this;
	}
	FRotator& operator*(const FRotator& o)
	{
		pitch *= o.pitch;
		yaw *= o.yaw;
		roll *= o.roll;
		return *this;
	}
	FRotator& operator/(const FRotator& o)
	{
		pitch /= o.pitch;
		yaw /= o.yaw;
		roll /= o.roll;
		return *this;
	}

	FRotator& operator+(float o)
	{
		pitch += o;
		yaw += o;
		roll += o;
		return *this;
	}
	FRotator& operator-(float o)
	{
		pitch -= o;
		yaw -= o;
		roll -= o;
		return *this;
	}
	FRotator& operator*(float o)
	{
		pitch *= o;
		yaw *= o;
		roll *= o;
		return *this;
	}
	FRotator& operator/(float o)
	{
		pitch /= o;
		yaw /= o;
		roll /= o;
		return *this;
	}

	D3DXVECTOR3 ToVector3()
	{
		return D3DXVECTOR3(pitch, yaw, roll);
	}
	operator D3DXVECTOR3() const
	{
		auto radPitch = static_cast<float>(pitch * 3.14159265358979323846 / 180.f);
		auto radYaw = static_cast<float>(yaw * 3.14159265358979323846 / 180.f);

		auto SP = static_cast<float>(sin(radPitch));
		auto CP = static_cast<float>(cos(radPitch));
		auto SY = static_cast<float>(sin(radYaw));
		auto CY = static_cast<float>(cos(radYaw));

		return D3DXVECTOR3(CP * CY, CP * SY, SP);
	}
};
