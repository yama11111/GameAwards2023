#include "Stage.h"
#include <cmath>

void Stage::Update(void)
{
    MiningOperatorPieceTabs();

    YMath::Vector2 recordpos{};
    ExplorateNearTabs(recordpos);

    ConfirmOperatorPiecePos(recordpos);

    SelectPieceForOperatorDebug();
}

void Stage::Draw(void)
{
    for (size_t i = 0; i < pieceVector_.size(); i++)
    {
        pieceVector_[i]->Draw();
    }

    //DrawFormatString(0, 0, 0xffffff, isPossibleInPiece_ && pieceVector_[indexNoOperatorPiece_]->GetTabs()[indexInPieceOtherTab_].isConnected_ == false && pieceVector_[indexOperatorPiece_]->GetTabs()[indexInPieceMineTab_].isTab_ - pieceVector_[indexNoOperatorPiece_]->GetTabs()[indexInPieceOtherTab_].isTab_ != 0 && pieceVector_[indexNoOperatorPiece_]->GetFixity() ? "ready to InPiece" : "no ready to InPiece");
    //DrawFormatString(0, 20, 0xff0000, isReset_ ? "execute reset" : "do not permission to reset");
}

void Stage::AddPiece(Piece* ptr)
{
    pieceVector_.emplace_back(ptr);
}

void Stage::OperatePiece(int index)
{
    if (pieceVector_[index]->GetState() == Piece::State::ROOT) {
        return;
    }

    if (pieceVector_[index]->GetState() == Piece::State::IMMUTABLE) {
        isReset_ = true;
        return;
    }

    for (size_t i = 0; i < pieceVector_.size(); i++)
    {
        pieceVector_[i]->SetOperator(false);
    }
    pieceVector_[index]->SetOperator(true);
    pieceVector_[index]->SetFixity(false);

    // 相手の接続解除
    for (size_t i = 0; i < pieceVector_[index]->GetTabs().size(); i++)
    {
        Piece::Tab_t* tabPtr{ &pieceVector_[index]->GetTabsRef()[i] };
        pieceVector_[tabPtr->indexOtherPiece_]->GetTabsRef()[tabPtr->indexOthertab_].isConnected_ = false;
        pieceVector_[tabPtr->indexOtherPiece_]->GetBlocksPtr()->at(pieceVector_[tabPtr->indexOtherPiece_]->GetTabsRef()[tabPtr->indexOthertab_].indexBlockVector_)->SetEntranceOpen(false);
    }

    permissionTabsAccess_ = true;
}

void Stage::InternalUpdatePieces(int index)
{
    pieceVector_[index]->Update();
}

void Stage::MiningOperatorPieceTabs(void)
{
    // ピース総当たり検索
    for (size_t i = 0; i < pieceVector_.size(); i++)
    {
        InternalUpdatePieces(i);

        // 対象のPieceのisOperatorがtrueの時　※isOperatorがtrueになっているPieceは単一想定
        if (pieceVector_[i]->GetOperator()) {
            // tabsをコピー
            operatorTabs_ = pieceVector_[i]->GetTabs();
            indexOperatorPiece_ = i;
        }
    }
}

void Stage::ExplorateNearTabs(YMath::Vector2& recordPos)
{
    // 該当pieceに付属するtab全てで検索
    for (size_t i = 0; i < operatorTabs_.size(); i++)
    {
        // 他の全てのpieceを検索
        for (size_t j = 0; j < pieceVector_.size(); j++)
        {
            if (j == indexOperatorPiece_) continue;

            // 他Pieceのtabをすべて検索
            for (size_t k = 0; k < pieceVector_[j]->GetTabs().size(); k++)
            {
                // 関数呼び出しの回数を抑制
                YMath::Vector2 noOpTabPos{ pieceVector_[j]->GetTabs()[k].pos_ };
                // 該当tabから半径detectRadius_以内に、他tabがあるか確認
                if (std::fabs(operatorTabs_[i].pos_.x_ - noOpTabPos.x_) <= detectRadius_ &&
                    std::fabs(operatorTabs_[i].pos_.y_ - noOpTabPos.y_) <= detectRadius_) {
                    // 該当tabと他tabの方向（Piece::Dir）が適正であるか確認
                    if (static_cast<int>(operatorTabs_[i].dir_) + static_cast<int>(pieceVector_[j]->GetTabs()[k].dir_) == 3) {
                        //isPossibleInPiece_ = true;
                        // 該当Pieceの中心座標を再計算
                        recordPos = { noOpTabPos.x_ + pieceVector_[indexOperatorPiece_]->GetPos().x_ - operatorTabs_[i].pos_.x_, noOpTabPos.y_ + pieceVector_[indexOperatorPiece_]->GetPos().y_ - operatorTabs_[i].pos_.y_ };
                        // 該当tabのindexを保存
                        indexInPieceMineTab_ = i;
                        indexNoOperatorPiece_ = j;
                        indexInPieceOtherTab_ = k;
                    }
                }
            }
        }
    }

    // 操作pieceが単一であることを考慮して、操作pieceが存在しない場合、operatorTabsは中身がないので例外スローが発生する。
    // しれを回避するためのbool
    if (permissionTabsAccess_) {
        if (indexOperatorPiece_ != indexNoOperatorPiece_) {
            if (std::fabs(operatorTabs_[indexInPieceMineTab_].pos_.x_ - pieceVector_[indexNoOperatorPiece_]->GetTabs()[indexInPieceOtherTab_].pos_.x_) <= detectRadius_ &&
                std::fabs(operatorTabs_[indexInPieceMineTab_].pos_.y_ - pieceVector_[indexNoOperatorPiece_]->GetTabs()[indexInPieceOtherTab_].pos_.y_) <= detectRadius_) {
                isPossibleInPiece_ = true;
            }
            else {
                isPossibleInPiece_ = false;
            }
        }
    }
}

void Stage::ConfirmOperatorPiecePos(const YMath::Vector2& pos)
{
    if (keysPtr_->IsTrigger(DIK_RETURN)) {
        if (isPossibleInPiece_ && pieceVector_[indexNoOperatorPiece_]->GetTabs()[indexInPieceOtherTab_].isConnected_ == false) {
            if (pieceVector_[indexOperatorPiece_]->GetTabs()[indexInPieceMineTab_].isTab_ - pieceVector_[indexNoOperatorPiece_]->GetTabs()[indexInPieceOtherTab_].isTab_ != 0 && pieceVector_[indexNoOperatorPiece_]->GetFixity()) {
                permissionTabsAccess_ = false;

                // 1群
                // 該当Pieceの中心点をExplorateNearTabs()で取得した値に変更。
                pieceVector_[indexOperatorPiece_]->SetPos(pos);
                // 該当PieceのTabsから接続状態の有無を変更 ※3群に移動
                //pieceVector_[indexOperatorPiece_]->GetTabsRef()[indexInPieceMineTab_].isConnected_ = true;
                //// 該当Pieceの接続tabのisEntranceOpenをtrueに変更 ※3群に移動
                //pieceVector_[indexOperatorPiece_]->GetBlocksPtr()->at(operatorTabs_[indexInPieceMineTab_].indexBlockVector_)->SetEntranceOpen(true);
                // 該当PieceのTabsから接続者か被接続者かの有無を変更
                pieceVector_[indexOperatorPiece_]->GetTabsRef()[indexInPieceMineTab_].isConnectExecuter_ = true;
                // 該当Pieceをはめ込んだので固定
                pieceVector_[indexOperatorPiece_]->SetFixity(true);
                // 該当pieceの接続tabに接続先のPieceの要素数を保存する（辿れるように）
                pieceVector_[indexOperatorPiece_]->GetTabsRef()[indexInPieceMineTab_].indexOtherPiece_ = indexNoOperatorPiece_;
                // 該当pieceの接続tabに接続先のtabの要素数を保存する（辿れるように）
                pieceVector_[indexOperatorPiece_]->GetTabsRef()[indexInPieceMineTab_].indexOthertab_ = indexInPieceOtherTab_;

                // 2群
                // 他Pieceの接続tabのisEntranceOpenをtrueに変更
                size_t elem{ pieceVector_[indexNoOperatorPiece_]->GetTabs()[indexInPieceOtherTab_].indexBlockVector_ };
                pieceVector_[indexNoOperatorPiece_]->GetBlocksPtr()->at(elem)->SetEntranceOpen(true);
                // 他PieceのTabsから接続状態の有無を変更
                pieceVector_[indexNoOperatorPiece_]->GetTabsRef()[indexInPieceOtherTab_].isConnected_ = true;
                // 他PieceのTabsから接続者か被接続者かの有無を変更
                pieceVector_[indexNoOperatorPiece_]->GetTabsRef()[indexInPieceOtherTab_].isConnectExecuter_ = false;
                // 他Pieceもはめ込んだことにする
                pieceVector_[indexNoOperatorPiece_]->SetFixity(true);

                // 3群
                // 該当Pieceの中心点等を変更したので、Update()を実行
                pieceVector_[indexOperatorPiece_]->Update();
                pieceVector_[indexOperatorPiece_]->UpdateTabs();
                // 該当Pieceの接続tabのisEntranceOpenをtrueに変更 Update()内にEntranceをfalseにしてしまう関数が含まれているためこの位置
                pieceVector_[indexOperatorPiece_]->GetBlocksPtr()->at(operatorTabs_[indexInPieceMineTab_].indexBlockVector_)->SetEntranceOpen(true);
                // 該当PieceのTabsから接続状態の有無を変更 同上
                pieceVector_[indexOperatorPiece_]->GetTabsRef()[indexInPieceMineTab_].isConnected_ = true;
                // 該当Pieceの操作権を放棄
                pieceVector_[indexOperatorPiece_]->SetOperator(false);
                // 該当Pieceのtabsコピーを破棄
                operatorTabs_.clear();
                // 該当Pieceはめ込み可能か知らせるフラグをfalseに変更。
                isPossibleInPiece_ = false;

                // 該当Pieceの該当tab以外に接続可能なほど他tabと近い（接続見込みとして構成されたステージのため）該当Pieceのtabがないか確認
                for (size_t i = 0; i < pieceVector_[indexOperatorPiece_]->GetTabs().size(); i++)
                {
                    // 該当Pieceの該当tab(接続tab)は除外
                    if (indexInPieceMineTab_ == i) continue;

                    // 他の全てのpieceを検索
                    for (size_t j = 0; j < pieceVector_.size(); j++)
                    {
                        // 該当Pieceは除外
                        if (j == indexOperatorPiece_) continue;

                        // 他Pieceのtabをすべて検索
                        for (size_t k = 0; k < pieceVector_[j]->GetTabs().size(); k++)
                        {
                            // 他Pieceの他tabが既に接続済みならスキップ
                            if (pieceVector_[j]->GetTabs()[k].isConnected_ == true) continue;

                            // 関数呼び出しの回数を抑制
                            YMath::Vector2 noOpTabPos{ pieceVector_[j]->GetTabs()[k].pos_ };

                            // 該当Pieceの接続tabから誤差0.5ピクセル以内に、他tabがあるか確認
                            if (std::fabs(pieceVector_[indexOperatorPiece_]->GetTabs()[i].pos_.x_ - noOpTabPos.x_) <= 0.5f &&
                                std::fabs(pieceVector_[indexOperatorPiece_]->GetTabs()[i].pos_.y_ - noOpTabPos.y_) <= 0.5f) {
                                // 該当tabと他tabの方向（Piece::Dir）が適正であるか確認
                                if (static_cast<int>(pieceVector_[indexOperatorPiece_]->GetTabs()[i].dir_) + static_cast<int>(pieceVector_[j]->GetTabs()[k].dir_) == 3) {
                                    // 1群
                                    // 該当PieceのTabsから接続状態の有無を変更 ※3群に移動
                                    //pieceVector_[indexOperatorPiece_]->GetTabsRef()[indexInPieceMineTab_].isConnected_ = true;
                                    //// 該当Pieceの接続tabのisEntranceOpenをtrueに変更 ※3群に移動
                                    //pieceVector_[indexOperatorPiece_]->GetBlocksPtr()->at(operatorTabs_[indexInPieceMineTab_].indexBlockVector_)->SetEntranceOpen(true);
                                    // 該当PieceのTabsから接続者か被接続者かの有無を変更（この場合、同時にはめ込んだ判定のため true[接続者側]）
                                    pieceVector_[indexOperatorPiece_]->GetTabsRef()[i].isConnectExecuter_ = true;
                                    // 該当Pieceをはめ込んだので固定（冗長と分かってはいるが念のため）
                                    pieceVector_[indexOperatorPiece_]->SetFixity(true);
                                    // 該当pieceの接続tabに接続先のPieceの要素数を保存する（辿れるように）
                                    pieceVector_[indexOperatorPiece_]->GetTabsRef()[i].indexOtherPiece_ = indexNoOperatorPiece_;
                                    // 該当pieceの接続tabに接続先のtabの要素数を保存する（辿れるように）
                                    pieceVector_[indexOperatorPiece_]->GetTabsRef()[i].indexOthertab_ = indexInPieceOtherTab_;

                                    // 2群
                                    // 他Pieceの接続tabのisEntranceOpenをtrueに変更
                                    size_t elem{ pieceVector_[j]->GetTabs()[k].indexBlockVector_ };
                                    pieceVector_[j]->GetBlocksPtr()->at(elem)->SetEntranceOpen(true);
                                    // 他PieceのTabsから接続状態の有無を変更
                                    pieceVector_[j]->GetTabsRef()[k].isConnected_ = true;
                                    // 他PieceのTabsから接続者か被接続者かの有無を変更
                                    pieceVector_[j]->GetTabsRef()[k].isConnectExecuter_ = false;
                                    // 他Pieceもはめ込んだことにする（冗長とはわかっているが念のため）
                                    pieceVector_[j]->SetFixity(true);

                                    // 3群
                                    // tabsのUpdate()だけ実行しとく
                                    pieceVector_[indexOperatorPiece_]->UpdateTabsPos();
                                    // 該当Pieceの接続tabのisEntranceOpenをtrueに変更 Update()内にEntranceをfalseにしてしまう関数が含まれているためこの位置
                                    pieceVector_[indexOperatorPiece_]->GetBlocksPtr()->at(pieceVector_[indexOperatorPiece_]->GetTabs()[i].indexBlockVector_)->SetEntranceOpen(true);
                                    // 該当PieceのTabsから接続状態の有無を変更 同上
                                    pieceVector_[indexOperatorPiece_]->GetTabsRef()[i].isConnected_ = true;
                                    // 該当Pieceの操作権を放棄（冗長だと理解しているが念のため）
                                    pieceVector_[indexOperatorPiece_]->SetOperator(false);
                                    // 該当Pieceはめ込み可能か知らせるフラグをfalseに変更。（冗長なのは理解しているが念のため）
                                    isPossibleInPiece_ = false;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void Stage::SelectPieceForOperatorDebug(void)
{
    if (keysPtr_->IsDown(DIK_LSHIFT)) {
        if (keysPtr_->IsTrigger(DIK_0)) OperatePiece(0);
        if (keysPtr_->IsTrigger(DIK_1)) OperatePiece(1);
        if (keysPtr_->IsTrigger(DIK_2)) OperatePiece(2);
        if (keysPtr_->IsTrigger(DIK_3)) OperatePiece(3);
        if (keysPtr_->IsTrigger(DIK_4)) OperatePiece(4);
        if (keysPtr_->IsTrigger(DIK_5)) OperatePiece(5);
        if (keysPtr_->IsTrigger(DIK_6)) OperatePiece(6);
        if (keysPtr_->IsTrigger(DIK_7)) OperatePiece(7);
        if (keysPtr_->IsTrigger(DIK_8)) OperatePiece(8);
        if (keysPtr_->IsTrigger(DIK_9)) OperatePiece(9);
    }
    else {
        if (keysPtr_->IsTrigger(DIK_0)) pieceVector_[0]->SetOperator(false);
        if (keysPtr_->IsTrigger(DIK_1)) pieceVector_[1]->SetOperator(false);
        if (keysPtr_->IsTrigger(DIK_2)) pieceVector_[2]->SetOperator(false);
        if (keysPtr_->IsTrigger(DIK_3)) pieceVector_[3]->SetOperator(false);
        if (keysPtr_->IsTrigger(DIK_4)) pieceVector_[4]->SetOperator(false);
        if (keysPtr_->IsTrigger(DIK_5)) pieceVector_[5]->SetOperator(false);
        if (keysPtr_->IsTrigger(DIK_6)) pieceVector_[6]->SetOperator(false);
        if (keysPtr_->IsTrigger(DIK_7)) pieceVector_[7]->SetOperator(false);
        if (keysPtr_->IsTrigger(DIK_8)) pieceVector_[8]->SetOperator(false);
        if (keysPtr_->IsTrigger(DIK_9)) pieceVector_[9]->SetOperator(false);
    }
}
