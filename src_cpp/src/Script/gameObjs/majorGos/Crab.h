/*
 * ========================= Crab.h ==========================
 *                          -- tpr --
 *                                        CREATE -- 2019.05.08
 *                                        MODIFY -- 
 * ----------------------------------------------------------
 *   螃蟹
 * -----------------------
 */
#ifndef TPR_CRAB_H
#define TPR_CRAB_H

//-------------------- CPP --------------------//
#include <string>
#include <vector>
#include <functional>

//-------------------- Engine --------------------//
#include "tprAssert.h"
#include "GameObj.h"
#include "GameObjMesh.h"
#include "AnimFrameSet.h"
#include "PubBinaryValType.h"
#include "MapAltitude.h"
#include "Density.h"

#include "AI_Crab.h"


namespace gameObjs{//------------- namespace gameObjs ----------------


//-- 定义了 go.binary 的数据格式 --
inline std::vector<PubBinaryValType> crab_pubBinaryValTypes {
    PubBinaryValType::HP,
    PubBinaryValType::MP
};

struct Crab_PvtBinary{
    int      tmpVal  {};
    AI_Crab  ai_crab {};
};


class Crab{
public:
    Crab() = default;

    //--- 延迟init ---//
    static void init_in_autoMod(   goSpecId_t specID_,
                            GameObj &goRef_,
                            const IntVec2 &mpos_,
					        float fieldWeight_,
					        const MapAltitude &alti_,
					        const Density &_density );
    
private:

    //--  每次调用回调函数，都需要做的 指针重绑定 --
    inline static Crab_PvtBinary *rebind_ptr( GameObj &goRef_ ){
        return reinterpret_cast<Crab_PvtBinary*>(goRef_.get_pvtBinaryPtr());
    }

    static void bind( GameObj &goRef_ );
    static void rebind( GameObj &goRef_ );
    //--- callback ---//
    static void OnRenderUpdate( GameObj &goRef_ ); 
    static void OnLogicUpdate( GameObj &goRef_ ); 
    static void OnActionSwitch( GameObj &goRef_, ActionSwitchType type_ );
};

//=====< 本类 唯一的 保留实例 >=====
//inline Crab  crab {};

}//------------- namespace gameObjs: end ----------------
#endif 

