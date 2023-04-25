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

	// �����[��
	class RelayBug : public IParticle
	{

	private:

		// �J�n�n�_ ���� ���p�n�_ �܂ł̃t���O
		bool isStartToRelay_ = false;

		// �J�n�n�_ ���� ���p�n�_ �܂ł̃^�C�}�[
		YMath::Timer startToRelayTim_;
		

		// ���p�n�_ ���� �I���n�_ �܂ł̃t���O
		bool isRelayToEnd_ = false;
		
		// ���p�n�_ ���� �I���n�_ �܂ł̃^�C�}�[
		YMath::Timer relayToEndTim_;


		// �ʒu�C�[�W���O
		YMath::Ease<YMath::Vector3> posEas_;

		// �I���n�_�ۑ��p
		YMath::Vector3 end_;

	public:
		
		/// <summary>
		/// ����
		/// </summary>
		/// <param name="startToRelayFrame"> : �J�n�n�_ ���� ���p�n�_ �܂ł̎���</param>
		/// <param name="relayToEndFrame"> : ���p�n�_ ���� �I���n�_ �܂ł̎���</param>
		/// <param name="start"> : �J�n�n�_</param>
		/// <param name="relay"> : ���p�n�_</param>
		/// <param name="end"> : �I���n�_</param>
		/// <param name="rota"> : ��]</param>
		/// <param name="scale"> : �傫��</param>
		/// <param name="color"> : �F</param>
		void Emit(
			const uint32_t startToRelayFrame,
			const uint32_t relayToEndFrame,
			const YMath::Vector3& start,
			const YMath::Vector3& relay,
			const YMath::Vector3& end,
			const YMath::Vector3& rota,
			const YMath::Vector3& scale,
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

		~RelayBug() = default;
	};

	// �A
	class Bubble : public IParticle
	{

	private:

		// �ړ��X�s�[�h
		YMath::Vector3 moveSpeed_;

		// ��]�X�s�[�h
		YMath::Vector3 rotaSpeed_;


		// ���� + ���ŃX�P�[���p�p���[�X�C�b�`
		bool isScalePowerSwitch_ = false;
		
		// ���� + ���ŗp�X�P�[���p�p���[
		YMath::Power scalePow_;

		// ���� + ���ŗp�X�P�[���C�[�W���O
		YMath::Ease<float> scaleEas_;

	public:

		/// <summary>
		/// ����
		/// </summary>
		/// <param name="aliveTime"> : ��������</param>
		/// <param name="status"> : �g�����X�t�H�[���ݒ�X�e�[�^�X</param>
		/// <param name="moveSpeed"> : �ړ��X�s�[�h</param>
		/// <param name="rotaSpeed"> : ��]�X�s�[�h</param>
		/// <param name="color"> : �F</param>
		void Emit(
			const uint32_t aliveTime,
			const YGame::Transform::Status status,
			const YMath::Vector3& moveSpeed,
			const YMath::Vector3& rotaSpeed,
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

		~Bubble() = default;

	};

}
