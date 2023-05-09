#pragma once
#include "Sprite2D.h"
#include <array>

namespace YGame
{
	class UIButtonDrawer
	{

	private:

		// �{�^���X�v���C�g�z��
		std::array<Sprite2D*, 2> pButtonSpr_{};

		// ��������
		bool isPush_ = false;

	public:

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="pButtonTex"> : �{�^���e�N�X�`��</param>
		/// <param name="pPressedTex"> : �����ꂽ�{�^���e�N�X�`��</param>
		void Initialize(Texture* pButtonTex, Texture* pPressedTex);

		/// <summary>
		/// �X�V
		/// </summary>
		/// <param name="isPush"> : ��������</param>
		void Update(const bool isPush);

		/// <summary>
		/// �`��
		/// </summary>
		/// <param name="pObject"> : �I�u�W�F�N�g�|�C���^</param>
		void Draw(Sprite2D::Object* pObject);
	};
}

