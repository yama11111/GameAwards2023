#pragma once
#include "Mesh.h"
#include "IShaderSet.h"
#include "PipelineSet.h"
#include "ModelObject.h"
#include "ObjectConfig.h"

namespace YGame
{
	// モデルクラス
	class Model
	{

	private:

		// メッシュ配列
		std::vector<std::unique_ptr<Mesh>> meshes_;

		// ノード配列
		std::vector<std::unique_ptr<Node>> nodes_;

		// 非表示
		bool isInvisible_ = false;

		// ファイルパス
		std::string fileName_;

	private:

		// 静的モデル格納用vector配列
		static std::vector<std::unique_ptr<Model>> models_;

	public:

		/// <summary>
		/// 生成(立方体)
		/// </summary>
		/// <returns>モデルポインタ</returns>
		static Model* CreateCube();

		/// <summary>
		/// 生成(立方体)
		/// </summary>
		/// <param name="texFileName"> : 画像のファイル名</param>
		/// <returns>モデルポインタ</returns>
		static Model* CreateCube(const std::string& texFileName);

		/// <summary>
		/// モデル(.obj)読み込み
		/// </summary>
		/// <param name="modelFileName"> : モデルのフォルダ名 (objと同じ名前の時のみ) </param>
		/// <param name="isSmoothing"> : スムーシングするか</param>
		/// <returns>モデルポインタ</returns>
		static Model* LoadObj(const std::string& modelFileName, const bool isSmoothing);

		/// <summary>
		/// モデル(.obj)読み込み
		/// </summary>
		/// <param name="modelFileName"> : モデルのフォルダ名 (objと同じ名前の時のみ) </param>
		/// <param name="isSmoothing"> : スムーシングするか</param>
		/// <returns>モデルポインタ</returns>
		static Model* LoadFbx(const std::string& modelFileName, const bool isSmoothing);

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
		void SetDrawCommand(ModelObject* pObj, const DrawLocation& location);


		/// <summary>
		/// 非表示設定
		/// </summary>
		/// <param name="isInvisible"> : 非表示か</param>
		void SetInvisible(const bool isInvisible) { isInvisible_ = isInvisible; }


#pragma region FbxLoader

	public:

		// FBX読み込み用
		class FbxLoader
		{

		public:

			// 静的FBXマネージャー
			static FbxManager* sFbxMan_;

			// 静的FBXインポーター
			static FbxImporter* sFbxImp_;

		public:

			/// <summary>
			/// 静的初期化
			/// </summary>
			static void StaticInitialize();

			/// <summary>
			/// 静的終了処理
			/// </summary>
			static void StaticFinalize();

		public:

			/// <summary>
			/// 再帰的にノード構成を解析
			/// </summary>
			/// <param name="pModel"> : モデルポインタ</param>
			/// <param name="fbxNode"> : 解析するノード</param>
			/// <param name="isSmoothing"> : スムーシングするか</param>
			/// <param name="parent"> : 親ノード</param>
			static void ParseNodeRecursive(Model* pModel, FbxNode* fbxNode, const bool isSmoothing, Node* parent = nullptr);

		};

#pragma endregion


#pragma region Pipeline

	public:

		// パイプラインクラス
		class Pipeline
		{
		
		public:

			// ルートパラメータ番号
			enum class RootParameterIndex
			{
				TransformCB = 0, // 行列
				ColorCB = 1, // 色
				LightCB = 2, // 光
				MaterialCB = 3, // マテリアル
				TexDT = 4, // テクスチャ
			};

		private:

			// シェーダーセット
			class ShaderSet : public YDX::IShaderSet
			{

			public:

				// 頂点シェーダオブジェクト
				Microsoft::WRL::ComPtr<ID3DBlob> vsBlob_ = nullptr;

				// ピクセルシェーダオブジェクト
				Microsoft::WRL::ComPtr<ID3DBlob> psBlob_ = nullptr;

			public:

				/// <summary>
				/// シェーダーファイル読み込み
				/// </summary>
				void Load() override;

			};

		private:

			// パイプライン設定
			static std::array<YDX::PipelineSet, DrawLocationNum> sPipelineSets_;

		public:

			// 描画セット
			struct DrawSet
			{

			public:

				// モデルポインタ
				Model* pModel_;

				// モデル用オブジェクト
				ModelObject* pObj_;

			public:

				/// <summary> 
				/// 描画
				/// </summary>
				void Draw();

			};

		private:

			// 描画用リスト配列
			static std::array<std::list<std::unique_ptr<DrawSet>>, DrawLocationNum> sDrawSets_;

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
			/// <param name="drawSet"> : 描画セット</param>
			/// <param name="locaiton"> : 描画場所</param>
			static void StaticPushBackDrawSet(std::unique_ptr<DrawSet>& drawSet, const DrawLocation& location);

			/// <summary>
			/// 静的描画
			/// </summary>
			/// <param name="locaiton"> : 描画場所</param>
			static void StaticDraw(const DrawLocation& location);

		};

#pragma endregion

	public:

		Model() = default;

		~Model() = default;

	};
}
