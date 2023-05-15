// ���s����
static const int DireLightNum = 3;
struct DireLight
{
	float3 lightVec_;	 // ����
	float3 lightColor_;	 // �F
	uint active_;		 // ����t���O
};

// �_����
static const int PointLightNum = 3;
struct PointLight
{
	float3 lightPos_;	 // ���W
	float3 lightColor_;	 // �F
	float3 lightAtten_;	 // ���������W��
	uint active_;		 // ����t���O
};

// �X�|�b�g���C�g����
static const int SpotLightNum = 3;
//struct SpotLight
//{
//	float3 lightPos_;	 // ���W
//	float3 lightVec_;	 // ����
//	float3 lightColor_;	 // �F
//	float3 lightAtten_;	 // ���������W��
//	float  lightStartFactorAngleCos_; // �����J�n�p�x
//	float  lightEndFactorAngleCos_;	 // �����I���p�x
//	uint active_;		 // ����t���O
//};

struct LightGroup
{
	float3 ambientColor_; // �����F
	DireLight direLights_[DireLightNum]; // ���s����
	PointLight pointLights_[PointLightNum]; // �_����
	//SpotLight spotLights_[SpotLightNum]; // �X�|�b�g���C�g����
};