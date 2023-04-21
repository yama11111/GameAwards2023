#pragma once
#include "Model.h"
#include "Lerp.h"
#include "Timer.h"
#include "Power.h"

namespace YGame
{
	// �p�[�e�B�N�����N���X
	class IParticle
	{
	
	public:
		
		// �����t���O
		bool isAlive_ = false;
	
	protected:
		
		// �I�u�W�F�N�g
		std::unique_ptr<YGame::ModelObject> obj_;

		// �F
		std::unique_ptr<YGame::Color> color_;
		
		// �����^�C�}�[
		YMath::Timer aliveTim_;
	
	public:
		
		/// <summary>
		/// ������
		/// </summary>
		/// <param name="aliveTime"> : ��������</param>
		void Initialize(const uint32_t aliveTime);
		
		/// <summary>
		/// �����X�V
		/// </summary>
		/// <returns> : �����Ă��邩</returns>
		bool UpdateLife();

		/// <summary>
		/// �X�V
		/// </summary>
		virtual void Update() = 0;

		/// <summary>
		/// �`��
		/// </summary>
		virtual void Draw() = 0;
	
	protected:
		
		// �r���[�v���W�F�N�V�����|�C���^
		static YGame::ViewProjection* spVP_;
	
	public:

		/// <summary>
		/// �ÓI������
		/// </summary>
		/// <param name="pVP"> : �r���[�v���W�F�N�V�����|�C���^</param>
		static void StaticInitialize(YGame::ViewProjection* pVP);
	
	public:

		virtual ~IParticle() = default;
	
	};

	// ����O���b�h�u���b�N
	class IlluminationGridBlock : public IParticle
	{
	private:

		// �A���t�@�l�p�p���[
		YMath::Power alphaPow_;

		// �A���t�@�l�p���[�𓮂�����
		bool isActAlphaPower_ = false;

		// �A���t�@�l�C�[�W���O
		YMath::Ease<float> alphaEas_;

	public:

		/// <summary>
		/// ����
		/// </summary>
		/// <param name="aliveTime"> : ��������</param>
		/// <param name="pParent"> : �e�s��</param>
		/// <param name="color"> : �F</param>
		/// <param name="alphaEas"> : �A���t�@�l�C�[�W���O</param>
		void Emit(
			const uint32_t aliveTime,
			YMath::Matrix4* pParent,
			const YMath::Vector3& color,
			const YMath::Ease<float> alphaEas);

		/// <summary>
		/// �X�V
		/// </summary>
		void Update() override;

		/// <summary>
		/// �`��
		/// </summary>
		void Draw() override;

	private:

		// �ÓI���f���|�C���^
		static YGame::Model* spModel_;

	public:

		/// <summary>
		/// �ÓI������
		/// </summary>
		/// <param name="pModel"> : ���f���|�C���^</param>
		static void StaticInitialize(YGame::Model* pModel);

	public:

		~IlluminationGridBlock() = default;

	};

	// �ݒu�O���b�h�u���b�N
	class PlaceGridBlock : public IParticle
	{
	private:

		// �傫���C�[�W���O
		YMath::Ease<float> scaleEas_;

	public:

		/// <summary>
		/// ����
		/// </summary>
		/// <param name="aliveTime"> : ��������</param>
		/// <param name="pParent"> : �e�s��</param>
		/// <param name="scaleEas"> : �傫���C�[�W���O</param>
		/// <param name="color"> : �F</param>
		void Emit(
			const uint32_t aliveTime,
			YMath::Matrix4* pParent,
			const YMath::Ease<float> scaleEas,
			const YMath::Vector3& color);

		/// <summary>
		/// �X�V
		/// </summary>
		void Update() override;

		/// <summary>
		/// �`��
		/// </summary>
		void Draw() override;

	private:

		// �ÓI���f���|�C���^
		static YGame::Model* spModel_;

	public:

		/// <summary>
		/// �ÓI������
		/// </summary>
		/// <param name="pModel"> : ���f���|�C���^</param>
		static void StaticInitialize(YGame::Model* pModel);

	public:

		~PlaceGridBlock() = default;

	};
}
