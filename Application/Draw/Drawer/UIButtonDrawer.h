#pragma once
#include "Sprite2D.h"
#include <array>

namespace YGame
{
	class UIButtonDrawer
	{

	private:

		// ボタンスプライト配列
		std::array<Sprite2D*, 2> pButtonSpr_{};

		// 押したか
		bool isPush_ = false;

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="pButtonTex"> : ボタンテクスチャ</param>
		/// <param name="pPressedTex"> : 押されたボタンテクスチャ</param>
		void Initialize(Texture* pButtonTex, Texture* pPressedTex);

		/// <summary>
		/// 更新
		/// </summary>
		/// <param name="isPush"> : 押したか</param>
		void Update(const bool isPush);

		/// <summary>
		/// 描画
		/// </summary>
		/// <param name="pObject"> : オブジェクトポインタ</param>
		void Draw(Sprite2D::Object* pObject);
	};
}

