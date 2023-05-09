#pragma once
#include "Vertices.h"
#include "IShaderSet.h"
#include "PipelineSet.h"
#include "Texture.h"
#include "ObjectConfig.h"
#include "Transform.h"
#include "ViewProjection.h"
#include "Color.h"
#include <list>
#include <array>

namespace YGame
{

	// スプライト3Dクラス
	class Sprite3D
	{

	public:

		// オブジェクトクラス前方宣言
		class Object;

		// パイプラインクラス前方宣言
		class Pipeline;

	public:

		/// <summary>
		/// 生成
		/// </summary>
		/// <param name="pTex"> : テクスチャポインタ</param>
		/// <returns>スプライトポインタ</returns>
		static Sprite3D* Create(Texture* pTex);

		/// <summary>
		/// 全削除
		/// </summary>
		static void AllClear();

	public:

		/// <summary>
		/// 描画コマンド
		/// </summary>
		/// <param name="pObj"> : オブジェクトポインタ</param>
		/// <param name="locaiton"> : 描画場所</param>
		void SetDrawCommand(Object* pObj, const DrawLocation& location);

		/// <summary>
		/// 表示するか設定
		/// </summary>
		/// <param name="isVisible"> : 表示するか</param>
		void SetIsVisible(const bool isVisible);

	public:

		Sprite3D() = default;

		~Sprite3D() = default;

	public:

		// 頂点データ
		struct VData
		{
			YMath::Vector3 pos_; // xyz座標
		};

	private:

		// 頂点データ
		YDX::Vertices<VData> vt_;

		// テクスチャ
		Texture* pTex_ = nullptr;

		// 表示するか
		bool isVisible_ = true;

	private:

		// 静的スプライト3D格納用vector配列
		static std::vector<std::unique_ptr<Sprite3D>> sSprites_;

	};

#pragma region Object

	// スプライト3D用オブジェクトクラス
	class Sprite3D::Object : public Transform
	{

	public:

		/// <summary>
		/// 生成 + 初期化 (デフォルト初期化)
		/// </summary>
		/// <param name="status"> : 位置, 回転, 大きさ</param>
		/// <param name="isXAxisBillboard"> : X軸ビルボードか</param>
		/// <param name="isYAxisBillboard"> : Y軸ビルボードか</param>
		/// <param name="isMutable"> : シーン遷移時に開放するか</param>
		/// <returns>動的インスタンス (newされたもの)</returns>
		static Object* Create(
			const Status& status,
			bool isXAxisBillboard, bool isYAxisBillboard,
			const bool isMutable = true);

		/// <summary>
		/// 生成 + 初期化 (Transform以外は nullの時 デフォルトで初期化)
		/// </summary>
		/// <param name="status"> : 位置, 回転, 大きさ</param>
		/// <param name="isXAxisBillboard"> : X軸ビルボードか</param>
		/// <param name="isYAxisBillboard"> : Y軸ビルボードか</param>
		/// <param name="pVP"> : ビュープロジェクションポインタ</param>
		/// <param name="pColor"> : 色ポインタ</param>
		/// <param name="isMutable"> : シーン遷移時に開放するか</param>
		/// <returns>動的インスタンス (newされたもの)</returns>
		static Object* Create(
			const Status& status,
			bool isXAxisBillboard, bool isYAxisBillboard,
			ViewProjection* pVP,
			Color* pColor,
			const bool isMutable = true);

	public:
		
		/// <summary>
		/// ビュープロジェクション設定 (null = Default)
		/// </summary>
		/// <param name="pVP"> : ビュープロジェクションポインタ</param>
		void SetViewProjection(ViewProjection* pVP);

		/// <summary>
		/// 色設定 (null = Default)
		/// </summary>
		/// <param name="pColor"> : 色ポインタ</param>
		void SetColor(Color* pColor);

		/// <summary>
		/// ビルボード設定
		/// </summary>
		/// <param name="isXAxisBillboard"> : X軸ビルボードか</param>
		/// <param name="isYAxisBillboard"> : Y軸ビルボードか</param>
		void SetIsBillboard(bool isXAxisBillboard, bool isYAxisBillboard);

	public:

		/// <summary>
		/// 描画前コマンド
		/// </summary>
		/// <param name="transformRPIndex"></param>
		/// <param name="colorRPIndex"></param>
		void SetDrawCommand(const UINT transformRPIndex, const UINT colorRPIndex);

	private:

		Object() = default;

	public:

		~Object() = default;

	private:

		// 定数バッファデータ構造体
		struct CBData
		{
			YMath::Matrix4 matWorld_; // 3D変換行列
			YMath::Matrix4 matBill_; // ビルボード行列
		};

	private:

		// 定数バッファ (行列)
		YDX::ConstBuffer<CBData> cBuff_;

		// X軸ビルボード
		bool isXAxisBillboard_ = false;

		// Y軸ビルボード
		bool isYAxisBillboard_ = false;

		// ビュープロジェクションポインタ
		ViewProjection* pVP_ = nullptr;

		// 色ポインタ
		Color* pColor_ = nullptr;

	public:

		// 既定値クラス
		class Default
		{

		public:

			// ビュープロジェクションポインタ (デフォルト)
			static std::unique_ptr<ViewProjection> sVP_;

			// 色 (デフォルト)
			static std::unique_ptr<Color> sColor_;

		public:

			/// <summary>
			/// 静的初期化
			/// </summary>
			static void StaticInitialize();

		};

	};

#pragma endregion


#pragma region Pipeline

	// パイプラインクラス
	class Sprite3D::Pipeline
	{

	public:

		/// <summary>
		/// 静的初期化
		/// </summary>
		static void StaticInitialize();

		/// <summary>
		/// 静的描画リストクリア
		/// </summary>
		/// <param name="locaiton"> : 描画場所</param>
		static void StaticClearDrawSet(const DrawLocation& location);

		/// <summary>
		/// 静的描画セット挿入
		/// </summary>
		/// <param name="pSprite2D"> : スプライトポインタ</param>
		/// <param name="pObj"> : オブジェクトポインタ</param>
		/// <param name="locaiton"> : 描画場所</param>
		static void StaticPushBackDrawSet(Sprite3D* pSprite3D, Sprite3D::Object* pObj, const DrawLocation& location);

		/// <summary>
		/// 静的描画
		/// </summary>
		/// <param name="locaiton"> : 描画場所</param>
		static void StaticDraw(const DrawLocation& location);

	public:

		// ルートパラメータ番号
		enum class RootParameterIndex
		{
			TransformCB = 0, // 行列
			ColorCB = 1, // 色
			TexDT = 2, // テクスチャ
		};

	private:

		// シェーダーセット
		class ShaderSet : public YDX::IShaderSet
		{
		public:

			// 頂点シェーダオブジェクト
			Microsoft::WRL::ComPtr<ID3DBlob> vsBlob_ = nullptr;

			// ジオメトリシェーダオブジェクト
			Microsoft::WRL::ComPtr<ID3DBlob> gsBlob_ = nullptr;

			// ピクセルシェーダオブジェクト
			Microsoft::WRL::ComPtr<ID3DBlob> psBlob_ = nullptr;

		public:

			/// <summary>
			/// シェーダーファイル読み込み
			/// </summary>
			void Load() override;

		};

	public:

		// 描画セット
		struct DrawSet
		{

		public:

			// スプライト3Dポインタ
			Sprite3D* pSprite3D_;

			// スプライト3D用オブジェクト
			Sprite3D::Object* pObj_;

		public:

			/// <summary> 
			/// 描画
			/// </summary>
			void Draw();

		};

	private:

		// パイプライン設定配列
		static std::array<YDX::PipelineSet, DrawLocationNum> sPipelineSets_;

		// 描画用リスト配列
		static std::array<std::list<std::unique_ptr<DrawSet>>, DrawLocationNum> sDrawSets_;

	};

#pragma endregion

}