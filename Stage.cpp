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

    // ����̐ڑ�����
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
    // �s�[�X�������茟��
    for (size_t i = 0; i < pieceVector_.size(); i++)
    {
        InternalUpdatePieces(i);

        // �Ώۂ�Piece��isOperator��true�̎��@��isOperator��true�ɂȂ��Ă���Piece�͒P��z��
        if (pieceVector_[i]->GetOperator()) {
            // tabs���R�s�[
            operatorTabs_ = pieceVector_[i]->GetTabs();
            indexOperatorPiece_ = i;
        }
    }
}

void Stage::ExplorateNearTabs(YMath::Vector2& recordPos)
{
    // �Y��piece�ɕt������tab�S�ĂŌ���
    for (size_t i = 0; i < operatorTabs_.size(); i++)
    {
        // ���̑S�Ă�piece������
        for (size_t j = 0; j < pieceVector_.size(); j++)
        {
            if (j == indexOperatorPiece_) continue;

            // ��Piece��tab�����ׂČ���
            for (size_t k = 0; k < pieceVector_[j]->GetTabs().size(); k++)
            {
                // �֐��Ăяo���̉񐔂�}��
                YMath::Vector2 noOpTabPos{ pieceVector_[j]->GetTabs()[k].pos_ };
                // �Y��tab���甼�adetectRadius_�ȓ��ɁA��tab�����邩�m�F
                if (std::fabs(operatorTabs_[i].pos_.x_ - noOpTabPos.x_) <= detectRadius_ &&
                    std::fabs(operatorTabs_[i].pos_.y_ - noOpTabPos.y_) <= detectRadius_) {
                    // �Y��tab�Ƒ�tab�̕����iPiece::Dir�j���K���ł��邩�m�F
                    if (static_cast<int>(operatorTabs_[i].dir_) + static_cast<int>(pieceVector_[j]->GetTabs()[k].dir_) == 3) {
                        //isPossibleInPiece_ = true;
                        // �Y��Piece�̒��S���W���Čv�Z
                        recordPos = { noOpTabPos.x_ + pieceVector_[indexOperatorPiece_]->GetPos().x_ - operatorTabs_[i].pos_.x_, noOpTabPos.y_ + pieceVector_[indexOperatorPiece_]->GetPos().y_ - operatorTabs_[i].pos_.y_ };
                        // �Y��tab��index��ۑ�
                        indexInPieceMineTab_ = i;
                        indexNoOperatorPiece_ = j;
                        indexInPieceOtherTab_ = k;
                    }
                }
            }
        }
    }

    // ����piece���P��ł��邱�Ƃ��l�����āA����piece�����݂��Ȃ��ꍇ�AoperatorTabs�͒��g���Ȃ��̂ŗ�O�X���[����������B
    // �����������邽�߂�bool
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

                // 1�Q
                // �Y��Piece�̒��S�_��ExplorateNearTabs()�Ŏ擾�����l�ɕύX�B
                pieceVector_[indexOperatorPiece_]->SetPos(pos);
                // �Y��Piece��Tabs����ڑ���Ԃ̗L����ύX ��3�Q�Ɉړ�
                //pieceVector_[indexOperatorPiece_]->GetTabsRef()[indexInPieceMineTab_].isConnected_ = true;
                //// �Y��Piece�̐ڑ�tab��isEntranceOpen��true�ɕύX ��3�Q�Ɉړ�
                //pieceVector_[indexOperatorPiece_]->GetBlocksPtr()->at(operatorTabs_[indexInPieceMineTab_].indexBlockVector_)->SetEntranceOpen(true);
                // �Y��Piece��Tabs����ڑ��҂���ڑ��҂��̗L����ύX
                pieceVector_[indexOperatorPiece_]->GetTabsRef()[indexInPieceMineTab_].isConnectExecuter_ = true;
                // �Y��Piece���͂ߍ��񂾂̂ŌŒ�
                pieceVector_[indexOperatorPiece_]->SetFixity(true);
                // �Y��piece�̐ڑ�tab�ɐڑ����Piece�̗v�f����ۑ�����i�H���悤�Ɂj
                pieceVector_[indexOperatorPiece_]->GetTabsRef()[indexInPieceMineTab_].indexOtherPiece_ = indexNoOperatorPiece_;
                // �Y��piece�̐ڑ�tab�ɐڑ����tab�̗v�f����ۑ�����i�H���悤�Ɂj
                pieceVector_[indexOperatorPiece_]->GetTabsRef()[indexInPieceMineTab_].indexOthertab_ = indexInPieceOtherTab_;

                // 2�Q
                // ��Piece�̐ڑ�tab��isEntranceOpen��true�ɕύX
                size_t elem{ pieceVector_[indexNoOperatorPiece_]->GetTabs()[indexInPieceOtherTab_].indexBlockVector_ };
                pieceVector_[indexNoOperatorPiece_]->GetBlocksPtr()->at(elem)->SetEntranceOpen(true);
                // ��Piece��Tabs����ڑ���Ԃ̗L����ύX
                pieceVector_[indexNoOperatorPiece_]->GetTabsRef()[indexInPieceOtherTab_].isConnected_ = true;
                // ��Piece��Tabs����ڑ��҂���ڑ��҂��̗L����ύX
                pieceVector_[indexNoOperatorPiece_]->GetTabsRef()[indexInPieceOtherTab_].isConnectExecuter_ = false;
                // ��Piece���͂ߍ��񂾂��Ƃɂ���
                pieceVector_[indexNoOperatorPiece_]->SetFixity(true);

                // 3�Q
                // �Y��Piece�̒��S�_����ύX�����̂ŁAUpdate()�����s
                pieceVector_[indexOperatorPiece_]->Update();
                pieceVector_[indexOperatorPiece_]->UpdateTabs();
                // �Y��Piece�̐ڑ�tab��isEntranceOpen��true�ɕύX Update()����Entrance��false�ɂ��Ă��܂��֐����܂܂�Ă��邽�߂��̈ʒu
                pieceVector_[indexOperatorPiece_]->GetBlocksPtr()->at(operatorTabs_[indexInPieceMineTab_].indexBlockVector_)->SetEntranceOpen(true);
                // �Y��Piece��Tabs����ڑ���Ԃ̗L����ύX ����
                pieceVector_[indexOperatorPiece_]->GetTabsRef()[indexInPieceMineTab_].isConnected_ = true;
                // �Y��Piece�̑��쌠�����
                pieceVector_[indexOperatorPiece_]->SetOperator(false);
                // �Y��Piece��tabs�R�s�[��j��
                operatorTabs_.clear();
                // �Y��Piece�͂ߍ��݉\���m�点��t���O��false�ɕύX�B
                isPossibleInPiece_ = false;

                // �Y��Piece�̊Y��tab�ȊO�ɐڑ��\�ȂقǑ�tab�Ƌ߂��i�ڑ������݂Ƃ��č\�����ꂽ�X�e�[�W�̂��߁j�Y��Piece��tab���Ȃ����m�F
                for (size_t i = 0; i < pieceVector_[indexOperatorPiece_]->GetTabs().size(); i++)
                {
                    // �Y��Piece�̊Y��tab(�ڑ�tab)�͏��O
                    if (indexInPieceMineTab_ == i) continue;

                    // ���̑S�Ă�piece������
                    for (size_t j = 0; j < pieceVector_.size(); j++)
                    {
                        // �Y��Piece�͏��O
                        if (j == indexOperatorPiece_) continue;

                        // ��Piece��tab�����ׂČ���
                        for (size_t k = 0; k < pieceVector_[j]->GetTabs().size(); k++)
                        {
                            // ��Piece�̑�tab�����ɐڑ��ς݂Ȃ�X�L�b�v
                            if (pieceVector_[j]->GetTabs()[k].isConnected_ == true) continue;

                            // �֐��Ăяo���̉񐔂�}��
                            YMath::Vector2 noOpTabPos{ pieceVector_[j]->GetTabs()[k].pos_ };

                            // �Y��Piece�̐ڑ�tab����덷0.5�s�N�Z���ȓ��ɁA��tab�����邩�m�F
                            if (std::fabs(pieceVector_[indexOperatorPiece_]->GetTabs()[i].pos_.x_ - noOpTabPos.x_) <= 0.5f &&
                                std::fabs(pieceVector_[indexOperatorPiece_]->GetTabs()[i].pos_.y_ - noOpTabPos.y_) <= 0.5f) {
                                // �Y��tab�Ƒ�tab�̕����iPiece::Dir�j���K���ł��邩�m�F
                                if (static_cast<int>(pieceVector_[indexOperatorPiece_]->GetTabs()[i].dir_) + static_cast<int>(pieceVector_[j]->GetTabs()[k].dir_) == 3) {
                                    // 1�Q
                                    // �Y��Piece��Tabs����ڑ���Ԃ̗L����ύX ��3�Q�Ɉړ�
                                    //pieceVector_[indexOperatorPiece_]->GetTabsRef()[indexInPieceMineTab_].isConnected_ = true;
                                    //// �Y��Piece�̐ڑ�tab��isEntranceOpen��true�ɕύX ��3�Q�Ɉړ�
                                    //pieceVector_[indexOperatorPiece_]->GetBlocksPtr()->at(operatorTabs_[indexInPieceMineTab_].indexBlockVector_)->SetEntranceOpen(true);
                                    // �Y��Piece��Tabs����ڑ��҂���ڑ��҂��̗L����ύX�i���̏ꍇ�A�����ɂ͂ߍ��񂾔���̂��� true[�ڑ��ґ�]�j
                                    pieceVector_[indexOperatorPiece_]->GetTabsRef()[i].isConnectExecuter_ = true;
                                    // �Y��Piece���͂ߍ��񂾂̂ŌŒ�i�璷�ƕ������Ă͂��邪�O�̂��߁j
                                    pieceVector_[indexOperatorPiece_]->SetFixity(true);
                                    // �Y��piece�̐ڑ�tab�ɐڑ����Piece�̗v�f����ۑ�����i�H���悤�Ɂj
                                    pieceVector_[indexOperatorPiece_]->GetTabsRef()[i].indexOtherPiece_ = indexNoOperatorPiece_;
                                    // �Y��piece�̐ڑ�tab�ɐڑ����tab�̗v�f����ۑ�����i�H���悤�Ɂj
                                    pieceVector_[indexOperatorPiece_]->GetTabsRef()[i].indexOthertab_ = indexInPieceOtherTab_;

                                    // 2�Q
                                    // ��Piece�̐ڑ�tab��isEntranceOpen��true�ɕύX
                                    size_t elem{ pieceVector_[j]->GetTabs()[k].indexBlockVector_ };
                                    pieceVector_[j]->GetBlocksPtr()->at(elem)->SetEntranceOpen(true);
                                    // ��Piece��Tabs����ڑ���Ԃ̗L����ύX
                                    pieceVector_[j]->GetTabsRef()[k].isConnected_ = true;
                                    // ��Piece��Tabs����ڑ��҂���ڑ��҂��̗L����ύX
                                    pieceVector_[j]->GetTabsRef()[k].isConnectExecuter_ = false;
                                    // ��Piece���͂ߍ��񂾂��Ƃɂ���i�璷�Ƃ͂킩���Ă��邪�O�̂��߁j
                                    pieceVector_[j]->SetFixity(true);

                                    // 3�Q
                                    // tabs��Update()�������s���Ƃ�
                                    pieceVector_[indexOperatorPiece_]->UpdateTabsPos();
                                    // �Y��Piece�̐ڑ�tab��isEntranceOpen��true�ɕύX Update()����Entrance��false�ɂ��Ă��܂��֐����܂܂�Ă��邽�߂��̈ʒu
                                    pieceVector_[indexOperatorPiece_]->GetBlocksPtr()->at(pieceVector_[indexOperatorPiece_]->GetTabs()[i].indexBlockVector_)->SetEntranceOpen(true);
                                    // �Y��Piece��Tabs����ڑ���Ԃ̗L����ύX ����
                                    pieceVector_[indexOperatorPiece_]->GetTabsRef()[i].isConnected_ = true;
                                    // �Y��Piece�̑��쌠������i�璷���Ɨ������Ă��邪�O�̂��߁j
                                    pieceVector_[indexOperatorPiece_]->SetOperator(false);
                                    // �Y��Piece�͂ߍ��݉\���m�点��t���O��false�ɕύX�B�i�璷�Ȃ̂͗������Ă��邪�O�̂��߁j
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
