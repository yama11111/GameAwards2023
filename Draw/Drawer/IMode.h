#pragma once

// 状態クラス
class IMode
{

public:

	// タイプ
	enum class Type
	{
		Normal	 = 0, // 通常
		Movable  = 1, // 可動
	};

	// 状態の数
	static const size_t sTypeNum_ = 2;

	// 通常インデックス
	static const size_t sNormalIdx = static_cast<size_t>(IMode::Type::Normal);
	
	// 可動インデックス
	static const size_t sMovableIdx = static_cast<size_t>(IMode::Type::Movable);

private:

	// 現在のタイプ
	Type current_ = Type::Normal;

	// 現在のタイプ番号
	size_t currentIdx_ = sNormalIdx;

protected:

	/// <summary>
	/// 状態変更
	/// </summary>
	/// <param name="modeType"> : タイプ</param>
	void ChangeType(const Type& type);

protected:

	/// <summary>
	/// 現在のタイプ番号取得
	/// </summary>
	/// <returns>現在の状態番号</returns>
	size_t CurrentTypeIndex() { return currentIdx_; }

	/// <summary>
	/// 現在のタイプ取得
	/// </summary>
	/// <returns>現在の状態</returns>
	Type CurrentType() { return current_; }
};