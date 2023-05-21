#include "Sign.h"
#include <algorithm>
#include <cmath>
#include <imgui.h>

using namespace maruyama;

void Sign::Initialize(const Vector2& mapchipSize)
{
    //for (int y{}; y < (int)mapchipSize.y_; y++) {
//    mapchip2_.emplace_back(std::vector<std::unique_ptr<IBlock>>{});
//    for (int x{}; x < (int)mapchipSize.y_; x++) {
//        mapchip2_.emplace_back(new IBlock{});
//    }
//}

    for (int y{}; y < (int)mapchipSize.y_; y++) {
        // とりま矩形にする
        mapchip_.emplace_back(std::vector<int>{});
        for (int x{}; x < (int)mapchipSize.x_; x++) {
            if (y == 0 || y == (int)(mapchipSize.y_ - 1)) {
                mapchip_[y].emplace_back(1);
                BDrawerList_.emplace_back(new Info_t{ &topLeftPos_,Vector2{ x * blockRadius_ * 2 + blockRadius_, -y * blockRadius_ * 2 - blockRadius_ } }); // yがマイナスなのは、yの正方向が上だから。
                BDrawerList_.back()->Initialize(1);
            }
            else if (x == 0 || x == (int)(mapchipSize.x_ - 1)) {
                mapchip_[y].emplace_back(1);
                BDrawerList_.emplace_back(new Info_t{ &topLeftPos_,Vector2{ x * blockRadius_ * 2 + blockRadius_, -y * blockRadius_ * 2 - blockRadius_ } });
                BDrawerList_.back()->Initialize(1);
            }
            else {
                mapchip_[y].emplace_back(0);
            }
        }
    }
}

void Sign::Update(void)
{
    for (auto& bd : BDrawerList_) {
        bd->Update();
    }

    DrawDebug();
}

void Sign::Draw(void)
{
    for (auto& bd : BDrawerList_) {
        bd->Draw();
    }
}

void maruyama::Sign::DrawDebug(void)
{

    ImGui::Begin("SignMapchip");
    for (size_t y = 0; y < mapchip_.size(); y++)
    {
        for (size_t x = 0; x < mapchip_[0].size(); x++)
        {
            ImGui::Text("elem[%d][%d]", y, x);
            ImGui::Text("bt: %d", mapchip_[y][x]);
        }
    }
    ImGui::End();

    ImGui::Begin("SignBDList");
    for (auto& bd : BDrawerList_) {
        ImGui::Text("bdTrans: %f,%f.,%f", bd->transform_.pos_.x_, bd->transform_.pos_.y_, bd->transform_.pos_.z_);
    }
    ImGui::End();
}

void Sign::PPC(YukiMapchipCollider* ptr)
{
    // 移動量は正か負か
    bool velSignX = ptr->velocity_.x_ > 0 ? true : false;
    bool velSignY = ptr->velocity_.y_ > 0 ? true : false;

    // 接近値
    //Vector2 approach = { ptr->velocity_.x_ / 100.f, ptr->velocity_.y_ / 100.f };

    Vector2 approach{};
    if (ptr->velocity_.x_)
        velSignX ? approach.x_ = 0.01f : approach.x_ = -0.01f;
    if (ptr->velocity_.y_)
        velSignY ? approach.y_ = 0.01f : approach.y_ = -0.01f;

    approach.x_ = roundToDecimal(approach.x_, 4);
    approach.y_ = roundToDecimal(approach.y_, 4);
    //if (velSignX == false) approach.x_ = -approach.x_;
    //if (velSignY == false) approach.y_ = -approach.y_;
    Vector3 velCopy = ptr->velocity_;
    ptr->velocity_ = { 0,0,0 };

    // 左上
    // 仮移動後の座標でマップチップ配列の位置
    int mElemX = CalcMovedElemX(ptr->point_.TopLeft_.x_, velCopy.x_);
    int mElemY = CalcMovedElemY(ptr->point_.TopLeft_.y_, velCopy.y_);
    // 距離詰めを行ったかどうか
    bool isExeTL = false;
    // もし仮移動後がブロックなら徐々にブロックとの距離を詰める
    isExeTL = SlowlyFillingSpaceX(ptr, ptr->point_.TopLeft_.x_, approach, mElemX, mElemY) || SlowlyFillingSpaceY(ptr, ptr->point_.TopLeft_.y_, approach, mElemX, mElemY);

    // 右上
    // 仮移動後の座標でマップチップ配列の位置
    mElemX = CalcMovedElemX(ptr->point_.TopRight_.x_, velCopy.x_);
    mElemY = CalcMovedElemY(ptr->point_.TopRight_.y_, velCopy.y_);
    // 距離詰めを行ったかどうか
    bool isExeTR = false;
    // もし仮移動後がブロックなら徐々にブロックとの距離を詰める
    isExeTR = SlowlyFillingSpaceX(ptr, ptr->point_.TopRight_.x_, approach, mElemX, mElemY) || SlowlyFillingSpaceY(ptr, ptr->point_.TopRight_.y_, approach, mElemX, mElemY);

    // 左下
    // 仮移動後の座標でマップチップ配列の位置
    mElemX = CalcMovedElemX(ptr->point_.BottomLeft_.x_, velCopy.x_);
    mElemY = CalcMovedElemY(ptr->point_.BottomLeft_.y_, velCopy.y_);
    // 距離詰めを行ったかどうか
    bool isExeBL = false;
    // もし仮移動後がブロックなら徐々にブロックとの距離を詰める
    isExeBL = SlowlyFillingSpaceX(ptr, ptr->point_.BottomLeft_.x_, approach, mElemX, mElemY) || SlowlyFillingSpaceY(ptr, ptr->point_.BottomLeft_.y_, approach, mElemX, mElemY);

    // 右下
    // 仮移動後の座標でマップチップ配列の位置
    mElemX = CalcMovedElemX(ptr->point_.BottomRight_.x_, velCopy.x_);
    mElemY = CalcMovedElemY(ptr->point_.BottomRight_.y_, velCopy.y_);
    // 距離詰めを行ったかどうか
    bool isExeBR = false;
    // もし仮移動後がブロックなら徐々にブロックとの距離を詰める
    isExeBR = SlowlyFillingSpaceX(ptr, ptr->point_.BottomRight_.x_, approach, mElemX, mElemY) || SlowlyFillingSpaceY(ptr, ptr->point_.BottomRight_.y_, approach, mElemX, mElemY);

    if (!isExeTL && !isExeTR && !isExeBL && !isExeBR) ptr->velocity_ = velCopy;













    ////// ブロックにはまっているかどうか
    ////bool isStuck{ false };
    //// 値を静的保持 [ばね関連]
    //static bool isSpring{};
    //static float springValue{};

    //// 左上
    //int elemX = CalcMovedElemX(ptr->point_.TopLeft_.x_, ptr->velocity_.x_);
    //int elemY = CalcMovedElemY(ptr->point_.TopLeft_.y_, ptr->velocity_.y_);
    //// 補正値格納変数
    //Vector2 TL{};
    //// 移動後の座標がマップチップ上だとブロックかどうか
    //if (static_cast<BlockType>(mapchip_[elemY][elemX]) == BlockType::BASIC) {
    //    Vector2 surplus{};
    //    surplus.x_ = std::fabs(topLeftPos_.x_ + (elemX + 1) * blockRadius_ * 2); // 左上から右方向にカウントするので topLeft + offsetX
    //    surplus.y_ = std::fabs(topLeftPos_.y_ - (elemY + 1) * blockRadius_ * 2); // 左上から下方向にカウントするので topLeft - offsetY

    //    ptr->velocity_.x_ > 0 ?
    //        TL.x_ = -surplus.x_ :
    //        TL.x_ = surplus.x_;
    //    ptr->velocity_.y_ > 0 ?
    //        TL.y_ = -surplus.y_ :
    //        TL.y_ = surplus.y_;
    //}

    //// 右上
    //elemX = CalcMovedElemX(ptr->point_.TopRight_.x_, ptr->velocity_.x_);
    //elemY = CalcMovedElemY(ptr->point_.TopRight_.y_, ptr->velocity_.y_);
    //// 補正値格納変数
    //Vector2 TR{};
    //// 移動後の座標がマップチップ上だとブロックかどうか
    //if (static_cast<BlockType>(mapchip_[elemY][elemX]) == BlockType::BASIC) {
    //    Vector2 surplus{};
    //    surplus.x_ = std::fabs(topLeftPos_.x_ + elemX * blockRadius_ * 2); // 左上から右方向にカウントするので topLeft + offsetX
    //    surplus.y_ = std::fabs(topLeftPos_.y_ - (elemY + 1) * blockRadius_ * 2); // 左上から下方向にカウントするので topLeft - offsetY

    //    ptr->velocity_.x_ > 0 ?
    //        TR.x_ = -surplus.x_ :
    //        TR.x_ = surplus.x_;
    //    ptr->velocity_.y_ > 0 ?
    //        TR.y_ = -surplus.y_ :
    //        TR.y_ = surplus.y_;
    //}

    //// 左下
    //elemX = CalcMovedElemX(ptr->point_.BottomLeft_.x_, ptr->velocity_.x_);
    //elemY = CalcMovedElemY(ptr->point_.BottomLeft_.y_, ptr->velocity_.y_);
    //// 補正値格納変数
    //Vector2 BL{};
    //// 移動後の座標がマップチップ上だとブロックかどうか
    //if (static_cast<BlockType>(mapchip_[elemY][elemX]) == BlockType::BASIC) {
    //    Vector2 surplus{};
    //    surplus.x_ = std::fabs(topLeftPos_.x_ + (elemX + 1) * blockRadius_ * 2); // 左上から右方向にカウントするので topLeft + offsetX
    //    surplus.y_ = std::fabs(topLeftPos_.y_ - elemY * blockRadius_ * 2); // 左上から下方向にカウントするので topLeft - offsetY

    //    ptr->velocity_.x_ > 0 ?
    //        BL.x_ = -surplus.x_ :
    //        BL.x_ = surplus.x_;
    //    ptr->velocity_.y_ > 0 ?
    //        BL.y_ = -surplus.y_ :
    //        BL.y_ = surplus.y_;
    //}
    //else if (static_cast<BlockType>(mapchip_[elemY][elemX]) == BlockType::SPRING) {
    //    isSpring = true;
    //    springValue = springPower_; // 値を設定された値に変更
    //}

    //// 右下
    //elemX = CalcMovedElemX(ptr->point_.BottomRight_.x_, ptr->velocity_.x_);
    //elemY = CalcMovedElemY(ptr->point_.BottomRight_.y_, ptr->velocity_.y_);
    //// 補正値格納変数
    //Vector2 BR{};
    //// 移動後の座標がマップチップ上だとブロックかどうか
    //if (static_cast<BlockType>(mapchip_[elemY][elemX]) == BlockType::BASIC) {
    //    Vector2 surplus{};
    //    surplus.x_ = std::fabs(topLeftPos_.x_ + elemX * blockRadius_ * 2); // 左上から右方向にカウントするので topLeft + offsetX
    //    surplus.y_ = std::fabs(topLeftPos_.y_ - elemY * blockRadius_ * 2); // 左上から下方向にカウントするので topLeft - offsetY

    //    ptr->velocity_.x_ > 0 ?
    //        BR.x_ = -surplus.x_ :
    //        BR.x_ = surplus.x_;
    //    ptr->velocity_.y_ > 0 ?
    //        BR.y_ = -surplus.y_ :
    //        BR.y_ = surplus.y_;
    //}
    //else if (static_cast<BlockType>(mapchip_[elemY][elemX]) == BlockType::SPRING) {
    //    isSpring = true;
    //    springValue = springPower_; // 値を設定された値に変更
    //}

    //// 一般的なブロックに対する押し戻し処理
    //Vector2 totalVel{};
    //// 左辺
    //CalcTotal(totalVel, TL);
    //CalcTotal(totalVel, TR);
    //CalcTotal(totalVel, BL);
    //CalcTotal(totalVel, BR);
    //if (totalVel.Length())
    //    ptr->velocity_ = { totalVel.x_,totalVel.y_,0 };

    //// ばねブロックに対する特殊挙動
    //if (isSpring && ptr->entityType_ == YukiMapchipCollider::EntityType::PLAYER) { // フラグがtrue && 対象がPlayerであること
    //    // どんだけ跳ねるか
    //    springValue -= springFall_; // 跳躍力は徐々に減衰する

    //    // 跳躍力が既に0になっている場合はフラグOFF
    //    if (springValue < 0.f) isSpring = false;
    //    // 跳躍力は決して0未満にはならない
    //    springValue = (std::max)(springValue, 0.f);

    //    // 移動量として代入
    //    ptr->velocity_.y_ += springValue;
    //}

    //// velocity格納用（呼び出し回数抑制 + 丸目誤差処理）
    //Vector2 vec2Vel{ roundToDecimal(ptr->velocity_.x_, 6),roundToDecimal(ptr->velocity_.y_, 6) };
    //// point格納用（呼び出し回数抑制 + 丸目誤差処理）
    //YukiMapchipCollider::Point pointCopy{};
    //pointCopy.TopLeft_.x_ = roundToDecimal(ptr->point_.TopLeft_.x_, 6);
    //pointCopy.TopLeft_.y_ = roundToDecimal(ptr->point_.TopLeft_.y_, 6);
    //pointCopy.TopRight_.x_ = roundToDecimal(ptr->point_.TopRight_.x_, 6);
    //pointCopy.TopRight_.y_ = roundToDecimal(ptr->point_.TopRight_.y_, 6);
    //pointCopy.BottomLeft_.x_ = roundToDecimal(ptr->point_.BottomLeft_.x_, 6);
    //pointCopy.BottomLeft_.y_ = roundToDecimal(ptr->point_.BottomLeft_.y_, 6);
    //pointCopy.BottomRight_.x_ = roundToDecimal(ptr->point_.BottomRight_.x_, 6);
    //pointCopy.BottomRight_.y_ = roundToDecimal(ptr->point_.BottomRight_.y_, 6);

    //// pointの座標をマップチップ単位に変換
    //int elemX{}, elemY{};
    //if (keys_->IsTrigger(DIK_P)) { // ブレイクポイント用
    //    int a{};
    //}
    ////<<<<<<<<<<<<<<<<<<<<<< 左上 >>>>>>>>>>>>>>>>>>>>>>>>>>//
    //elemX = pointCopy.TopLeft_.x_ / (int)(blockRadius_ * 2); // 要素数の計算
    //elemY = -1 * pointCopy.TopLeft_.y_ / (int)(blockRadius_ * 2); // 要素数は正、座標は負、算出は 座標 / 半径*2 で例外スローするので -をつける※yだけ
    //if (static_cast<BlockType>(mapchip_[elemY][elemX]) == BlockType::BASIC) // 通常ブロック
    //{
    //    isStuck = true;
    //}

    ////<<<<<<<<<<<<<<<<<<<<<< 右上 >>>>>>>>>>>>>>>>>>>>>>>>>>//
    //elemX = pointCopy.TopRight_.x_ / (int)(blockRadius_ * 2);
    //elemY = -1 * pointCopy.TopRight_.y_ / (int)(blockRadius_ * 2); // 要素数は正、座標は負、算出は 座標 / 半径*2 で例外スローするので -をつける※yだけ
    //if (static_cast<BlockType>(mapchip_[elemY][elemX]) == BlockType::BASIC) // 通常ブロック
    //{
    //    isStuck = true;
    //}

    ////<<<<<<<<<<<<<<<<<<<<<< 左下 >>>>>>>>>>>>>>>>>>>>>>>>>>//
    //elemX = pointCopy.BottomLeft_.x_ / (int)(blockRadius_ * 2);
    //elemY = -1 * pointCopy.BottomLeft_.y_ / (int)(blockRadius_ * 2); // 要素数は正、座標は負、算出は 座標 / 半径*2 で例外スローするので -をつける※yだけ
    //if (static_cast<BlockType>(mapchip_[elemY][elemX]) == BlockType::BASIC) // 通常ブロック
    //{
    //    isStuck = true;
    //}
    //else if (static_cast<BlockType>(mapchip_[elemY][elemX]) == BlockType::SPRING) // ばねブロック
    //{
    //    isSpring = true;
    //    springValue = springPower_; // 値を設定された値に変更
    //}

    ////<<<<<<<<<<<<<<<<<<<<<< 右下 >>>>>>>>>>>>>>>>>>>>>>>>>>//
    //elemX = pointCopy.BottomRight_.x_ / (int)(blockRadius_ * 2);
    //elemY = -1 * pointCopy.BottomRight_.y_ / (int)(blockRadius_ * 2); // 要素数は正、座標は負、算出は 座標 / 半径*2 で例外スローするので -をつける※yだけ
    //if (static_cast<BlockType>(mapchip_[elemY][elemX]) == BlockType::BASIC) // 通常ブロック
    //{
    //    isStuck = true;
    //}
    //else if (static_cast<BlockType>(mapchip_[elemY][elemX]) == BlockType::SPRING) // ばねブロック
    //{
    //    isSpring = true;
    //    springValue = springPower_; // 値を設定された値に変更
    //}

    //// CalcVelStuck用
    //{
    //    Vector2 TL{}, TR{}, BL{}, BR{};

    //    // 現在地（めり込んでる場合）の移動値を算出
    //    Vector2 vec2Vel{ ptr->velocity_.x_,ptr->velocity_.y_ };
    //    TL = CalcVelStuck(ptr->point_.TopLeft_); // 左上
    //    TR = CalcVelStuck(ptr->point_.TopRight_); // 右上
    //    BL = CalcVelStuck(ptr->point_.BottomLeft_); // 左下
    //    BR = CalcVelStuck(ptr->point_.BottomRight_); // 右下
    //}

    //// 4点の押し戻し移動量比較用
    //Vector2 TL{}, TR{}, BL{}, BR{};
    //// 一般的なブロック
    //if (isStuck) {
    //    TL = CalcVelMove(pointCopy.TopLeft_, vec2Vel); // 左上
    //    TR = CalcVelMove(pointCopy.TopRight_, vec2Vel); // 右上
    //    BL = CalcVelMove(pointCopy.BottomLeft_, vec2Vel); // 左下
    //    BR = CalcVelMove(pointCopy.BottomRight_, vec2Vel); // 右下

    //    // 算出された値の中で最小値を移動量として適用
    //    ptr->velocity_.x_ = (std::min)({ TL.x_,TR.x_,BL.x_,BR.x_ });
    //    ptr->velocity_.y_ = (std::min)({ TL.y_,TR.y_,BL.y_,BR.y_ });
    //    //// 算出された値の中で最大値を移動量として適用
    //    //ptr->velocity_.x_ = (std::max)({ TL.x_,TR.x_,BL.x_,BR.x_ });
    //    //ptr->velocity_.y_ = (std::max)({ TL.y_,TR.y_,BL.y_,BR.y_ });
    //}
    //// ばね
    //if (isSpring && ptr->entityType_ == YukiMapchipCollider::EntityType::PLAYER) { // フラグがtrue && 対象がPlayerであること
    //    // どんだけ跳ねるか
    //    springValue -= springFall_; // 跳躍力は徐々に減衰する

    //    // 跳躍力が既に0になっている場合はフラグOFF
    //    if (springValue < 0.f) isSpring = false;
    //    // 跳躍力は決して0未満にはならない
    //    springValue = (std::max)(springValue, 0.f);

    //    // 移動量として代入
    //    ptr->velocity_.y_ += springValue;
    //}

    // <summary>
    //## この構造の場合、コライダーを継承した子クラスたちのUpdate()関数は、
    //## 必ず下記のように最初の行以外での座標更新を行ってはならない。
    //## 最初の行: UpdatePos();
    //## それ以降: velocity計算;
    // </summary>
    //ptr->UpdatePos();
}

void maruyama::Sign::ReWriteBlock(size_t X, size_t Y, BlockType bt)
{
    // 対応外のブロック置換はスキップ
    if (bt == BlockType::WARP1 || bt == BlockType::WARP2) return;

    // 座標mapchipのint(blockType)書き換え
    mapchip_[Y][X] = static_cast<int>(bt);

    int x{ (int)X }, y{ (int)Y };
    // ブロックの管理リストへの追加
    BDrawerList_.emplace_back(new Info_t{ &topLeftPos_,Vector2{ x * blockRadius_ * 2 + blockRadius_, -y * blockRadius_ * 2 - blockRadius_ } });
    // 当該ブロックの初期化
    BDrawerList_.back()->Initialize(static_cast<int>(bt));
}

void maruyama::Sign::ReWriteBlock2Warp(size_t X, size_t Y, BlockType bt, Direction dirSelf)
{
    //<< WARP系ブロック限定が前提 >>//

    // 対応外のブロック置換はスキップ
    if (bt != BlockType::WARP1 && bt != BlockType::WARP2) return;

    // 座標mapchipのint(blockType)書き換え
    mapchip_[Y][X] = static_cast<int>(bt);

    int x{ (int)X }, y{ (int)Y };
    // ブロックの管理リストへの追加
    BDrawerList_.emplace_back(new Info_t{ &topLeftPos_,Vector2{ x * blockRadius_ * 2 + blockRadius_, -y * blockRadius_ * 2 - blockRadius_ } });
    // 当該ブロックの初期化
    BDrawerList_.back()->Initialize(static_cast<int>(bt));

    // ワープブロックの情報を専用リストに追加してマッピング管理※キーは対象の配列要素数
    warpInfos_.emplace_back(WarpIdx_t{ dirSelf,{X,Y} });
}

inline Sign::Vector3 maruyama::Sign::GetCenterPos(void)
{
    float x = (mapchip_[0].size() / 2) * blockRadius_ * 2;
    float y = (mapchip_.size() / 2) * blockRadius_ * 2;

    // trueで奇数
    if (mapchip_[0].size() % 2) x += blockRadius_;
    if (mapchip_.size() % 2) y += blockRadius_;

    return Vector3(topLeftPos_.x_ + x, topLeftPos_.y_ - y, topLeftPos_.z_);
}

float maruyama::Sign::roundToDecimal(float value, int decimalPlaces)
{
    float multiplier = (float)std::pow(10.0f, decimalPlaces);
    float roundedValue = (int)std::round(value * multiplier) / multiplier;
    return roundedValue;
}

bool maruyama::Sign::SlowlyFillingSpaceX(YukiMapchipCollider* ptr, float& pointX, const Vector2& approach, int mElemX, int mElemY)
{
    bool isExecuted = false;
    if (mElemX == -1 || mElemX == mapchip_[0].size()) return isExecuted;
    if (mElemY == -1 || mElemY == mapchip_.size()) return isExecuted;

    while (static_cast<BlockType>(mapchip_[mElemY][mElemX]) == BlockType::BASIC)
    {
        // 仮移動後の座標でマップチップ配列の位置
        int checkElemX = CalcMovedElemX(pointX, approach.x_);
        isExecuted = true;
        if (checkElemX == mElemX) break;

        ptr->transform_.pos_.x_ += approach.x_;
        ptr->UpdatePos();
        ptr->UpdatePoint();
    }
    return isExecuted;
}

bool maruyama::Sign::SlowlyFillingSpaceY(YukiMapchipCollider* ptr, float& pointY, const Vector2& approach, int mElemX, int mElemY)
{
    bool isExecuted = false;
    if (mElemX <= -1 || mElemX >= mapchip_[0].size()) return isExecuted;
    if (mElemY <= -1 || mElemY >= mapchip_.size()) return isExecuted;

    while (static_cast<BlockType>(mapchip_[mElemY][mElemX]) == BlockType::BASIC)
    {
        // 仮移動後の座標でマップチップ配列の位置
        int checkElemY = CalcMovedElemX(pointY, approach.y_);
        isExecuted = true;
        if (checkElemY == mElemY) break;

        ptr->transform_.pos_.y_ += approach.y_;
        ptr->UpdatePos();
        ptr->UpdatePoint();
    }
    return isExecuted;
}

