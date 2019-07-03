/*
 * ========================= Lichen_DForest.h ==========================
 *                          -- tpr --
 *                                        CREATE -- 2019.04.10
 *                                        MODIFY -- 
 * ----------------------------------------------------------
 *   地衣  mapSurface / DarkForest
 * ----------------------------
 */
#ifndef TPR_LICHEN_DARK_FOREST_H
#define TPR_LICHEN_DARK_FOREST_H

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


namespace gameObjs{//------------- namespace gameObjs ----------------


//-- 定义了 go.binary 的数据格式 --
inline std::vector<PubBinaryValType> lichen_DForest_pubBinaryValTypes {
    PubBinaryValType::HP,
    PubBinaryValType::MP
};

struct Lichen_DForest_PvtBinary{
    size_t   lichen_DForestId {0};
            //- 简单的从 几种款式中，随机挑选一款 [0,7]
    //===== padding =====//
    //...
};


class Lichen_DForest{
public:
    Lichen_DForest() = default;

    //--- 延迟init ---//
    static void init_in_autoMod(   goSpecId_t specID_,
                            GameObj &goRef_,
                            const IntVec2 &mpos_,
					        float fieldWeight_,
					        const MapAltitude &alti_,
					        const Density &_density );

private:

    //--  每次调用回调函数，都需要做的 指针重绑定 --
    inline static  Lichen_DForest_PvtBinary *rebind_ptr( GameObj &goRef_ ){
        return reinterpret_cast<Lichen_DForest_PvtBinary*>(goRef_.get_pvtBinaryPtr());
    }

    static void bind( GameObj &goRef_ );
    static void rebind( GameObj &goRef_ );

    //--- callback ---//
    static void OnRenderUpdate( GameObj &goRef_ ); 
    static void OnLogicUpdate( GameObj &goRef_ ); 
    static void OnActionSwitch( GameObj &goRef_, ActionSwitchType type_ );
};


}//------------- namespace gameObjs: end ----------------
#endif 


