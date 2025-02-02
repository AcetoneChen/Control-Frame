//
// Created by LEGION on 2021/10/4.
//
#include "ControlTask.h"


void CtrlHandle() {
    if (RemoteControl::rcInfo.sRight == DOWN_POS) {//右侧三档，急停模式
        ChassisStop();
        ArmStop();
    } else {//其他正常模式
        switch (RemoteControl::rcInfo.sLeft) {
            case UP_POS://左侧一档{
                if (RemoteControl::rcInfo.sRight == UP_POS) {
                    ChassisSetVelocity(RemoteControl::rcInfo.right_col * 2,
                                       RemoteControl::rcInfo.right_rol * 2, RemoteControl::rcInfo.left_rol);
                    Headmemory();
                }else if (RemoteControl::rcInfo.sRight == MID_POS){
                    StateMachine::stateHandle();
                  //  AutoSetVelocity();
                }
                break;
            case MID_POS://左侧二档
                if (RemoteControl::rcInfo.sRight == UP_POS) {
                    HeadlessSetVelocity(RemoteControl::rcInfo.right_col * 2,
                                        RemoteControl::rcInfo.right_rol * 2, RemoteControl::rcInfo.left_rol);
                    AutoChassisSet(0,0,PI/2);
                } else if (RemoteControl::rcInfo.sRight == MID_POS) {
                    HeadkeepSetVelocity(RemoteControl::rcInfo.right_col * 2,
                                        RemoteControl::rcInfo.right_rol * 2, RemoteControl::rcInfo.left_rol);
                }
                break;
            case DOWN_POS:
                if (RemoteControl::rcInfo.sRight == UP_POS) {
                    ArmSet(RemoteControl::rcInfo.left_col, RemoteControl::rcInfo.left_col * 90,RemoteControl::rcInfo.left_col);
                }
                break;
            default:
                break;
        }

    }

}
/*
void CtrlHandle() {
    if (RemoteControl::rcInfo.sRight == DOWN_POS) {//右侧三档，急停模式
        ChassisStop();
        ArmStop();
    } else {//其他正常模式
        switch (RemoteControl::rcInfo.sLeft) {
            case UP_POS://左侧一档{
                if (RemoteControl::rcInfo.sRight == UP_POS) {
                    ChassisSetVelocity(RemoteControl::rcInfo.right_col * 8,
                                       RemoteControl::rcInfo.right_rol * 8, RemoteControl::rcInfo.left_rol*2);
                    //ArmSet(RemoteControl::rcInfo.left_col, RemoteControl::rcInfo.left_col * 90,RemoteControl::rcInfo.left_col);
                    AutoClawSet(0);
                    Headmemory();
                }else if (RemoteControl::rcInfo.sRight == MID_POS){
                    ChassisSetVelocity(RemoteControl::rcInfo.right_col * 8,
                                       RemoteControl::rcInfo.right_rol * 8, RemoteControl::rcInfo.left_rol*2);
                    AutoClawSet(1);
                }
                break;
            case MID_POS://左侧二档
                if (RemoteControl::rcInfo.sRight == UP_POS) {
                    ArmSet(RemoteControl::rcInfo.right_rol * -1.57f,
                           RemoteControl::rcInfo.left_rol * -130,0);
                    AutoClawSet(0);
                } else if (RemoteControl::rcInfo.sRight == MID_POS) {
                    ArmSet(RemoteControl::rcInfo.right_rol* -1.57f,
                           RemoteControl::rcInfo.left_rol * -130,0);
                    AutoClawSet(1);
                }
                break;
            case DOWN_POS:
                if (RemoteControl::rcInfo.sRight == UP_POS) {
                    AutoSetVelocity();
                }
                break;
            default:
                break;
        }

    }

}*/
