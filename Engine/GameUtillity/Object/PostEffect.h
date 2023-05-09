//#pragma once
//#include "Vertices.h"
//#include "IShaderSet.h"
//#include "PipelineSet.h"
//#include "Texture.h"
//#include "Vector2.h"
//#include "ObjectConfig.h"
//#include <list>
//#include <array>
//
//namespace YGame
//{
//	class PostEffect
//	{
//
//	public:
//
//		// オブジェクトクラス前方宣言
//		class Object;
//
//		// パイプラインクラス前方宣言
//		class Pipeline;
//	
//	public:
//
//		void Draw();
//
//	public:
//
//		PostEffect() = default;
//
//		~PostEffect() = default;
//
//	};
//
//
//#pragma region Pipeline
//
//	// パイプラインクラス
//	class Pipeline
//	{
//
//	public:
//
//		/// <summary>
//		/// 静的初期化
//		/// </summary>
//		static void StaticInitialize();
//
//		/// <summary>
//		/// 静的描画リストクリア
//		/// </summary>
//		/// <param name="locaiton"> : 描画場所</param>
//		static void StaticClearDrawSet(const DrawLocation& location);
//
//		/// <summary>
//		/// 静的描画セット挿入
//		/// </summary>
//		/// <param name="drawSet"> : 描画セット</param>
//		/// <param name="locaiton"> : 描画場所</param>
//		static void StaticPushBackDrawSet(std::unique_ptr<DrawSet>& drawSet, const DrawLocation& location);
//
//		/// <summary>
//		/// 静的描画
//		/// </summary>
//		/// <param name="locaiton"> : 描画場所</param>
//		static void StaticDraw(const DrawLocation& location);
//
//	public:
//
//		// ルートパラメータ番号
//		enum class RootParameterIndex
//		{
//			TransformCB = 0, // 行列
//			ColorCB = 1, // 色
//			TexDT = 2, // テクスチャ
//		};
//
//	private:
//
//		// シェーダーセット
//		class ShaderSet : public YDX::IShaderSet
//		{
//		public:
//
//			// 頂点シェーダオブジェクト
//			Microsoft::WRL::ComPtr<ID3DBlob> vsBlob_ = nullptr;
//
//			// ピクセルシェーダオブジェクト
//			Microsoft::WRL::ComPtr<ID3DBlob> psBlob_ = nullptr;
//
//		public:
//
//			/// <summary>
//			/// シェーダーファイル読み込み
//			/// </summary>
//			void Load() override;
//
//		};
//
//	public:
//
//		// 描画セット
//		struct DrawSet
//		{
//
//		public:
//
//			// スプライト2Dポインタ
//			Sprite2D* pSprite2D_;
//
//			// スプライト2D用オブジェクト
//			Sprite2DObject* pObj_;
//
//		public:
//
//			/// <summary> 
//			/// 描画
//			/// </summary>
//			void Draw();
//
//		};
//
//	private:
//
//		// パイプライン設定
//		static YDX::PipelineSet sPipelineSets_;
//
//		// 描画用リスト配列
//		static std::array<std::list<std::unique_ptr<DrawSet>>, DrawLocationNum> sDrawSets_;
//
//	};
//
//#pragma endregion
//
//}
