/*
 * ========================= GameObj.h ==========================
 *                          -- tpr --
 *                                        创建 -- 2018.11.24
 *                                        修改 -- 2018.11.24
 * ----------------------------------------------------------
 *    GameObj 是游戏中的 一等公民。
 *    可以作为一个 独立的单位，存在于 游戏中
 * ----------------------------
 */
#ifndef _TPR_GAME_OBJ_H_
#define _TPR_GAME_OBJ_H_

//--- glm - 0.9.8 ---
#include <glm/glm.hpp>
            //-- glm::vec2
            //-- glm::vec3
            //-- glm::vec4
            //-- glm::mat4
#include <glm/gtc/matrix_transform.hpp>
            //-- glm::translate
            //-- glm::rotate
            //-- glm::scale
            //-- glm::perspective
#include <glm/gtc/type_ptr.hpp> 
            //-- glm::value_ptr

//-------------------- CPP --------------------//
#include <string>
#include <vector>
#include <functional>

//------------------- Libs --------------------//
#include "tprDataType.h" 

//------------------- SELF --------------------//
#include "GameObjType.h" 
#include "Mesh.h" 
#include "ID_Manager.h" 
#include "PixVec.h" 



//--- 最基础的 go 类，就像一个 "伪接口" ----//
// 具象go类 并不用继承 基础go类，而是 包含 一个go实例，
// 通过  动态绑定 来配置 这个被包含的 go实例的数据。
// 通过 function / bind 动态绑定各种回调函数
// 在 主引擎中，go类 是通用／官方认可的类型。也只通过这个 类来 访问 一切 go实例
//-------
//  并不存在孤立的 go实例，每个go实例，都被一个 具象go实例 所包含
//  goid 是全局唯一的。 其外层的 具象go实例 也使用这个 id号
//-------
//  go类 与 具象go类：
//  -- go类实例 负责存储实际的数据
//  -- 具象go类 只是一个 “装配工厂”，不存在 “具象go类实例”
class GameObj{

    using F_V_V = std::function<void()>;

public:
    GameObj() = default;

    void init();

    //-- disl <-> mem --//
    void  d2m( diskGameObj *_dgo );
    diskGameObj  m2d();

    //-----------------//
    //-- 几个经典的回调函数，tmp...
    F_V_V  Awake {nullptr};  //- 初始化阶段执行的 内容
    F_V_V  Start {nullptr};  //- 游戏在进入 主循环之前，执行的内容
    F_V_V  Update {nullptr}; //- 每一游戏帧，被主程序调用

    F_V_V  BeAffect {nullptr}; //- 当 本go实例 被外部 施加技能／影响 时，调用的函数
                                //- 未来会添加一个 参数：“被施加技能的类型”


    //----------------- vals ---------------//
    goid_t         id      {NULLID};    //- go实例 在程序中的 主要搜索依据。
    GameObjSpecies species {GameObjSpecies::NullSpecies}; //- go类型
    GameObjFamily  family  {GameObjFamily::Major};        //- go 类群


    bool   is_top_go  {true}; //- 是否为 顶层 go (有些go只是 其他go 的一部分)
    goid_t id_parent {NULLID}; //- 不管是否为顶层go，都可以有自己的 父go。
                             //- 如果没有，此项写 NULLID

    //--- go 状态 ----//
    bool              is_active {false}; //- 是否进入激活圈. 
                                        //   未进入激活圈的go，不参与任何逻辑运算，也不会被渲染
    GameObjState      state     {GameObjState::Sleep};         //- 常规状态
    GameObjMoveState  moveState {GameObjMoveState::BeMovable}; //- 运动状态
    

    PixVec2    targetPos {}; //- 目标pos，对齐与mapent 
    glm::vec2  currentPos {};  //- 当前帧 pos，float，不一定对齐与mapent
    glm::vec2  velocity {}; //- 运动速度

    float  weight {0}; //- go重量 （影响自己是否会被 一个 force 推动）


    bool is_default {true}; //- 是否为 默认go
                            //- “默认go” 意味着这个 go没有被游戏改写过。
                            //- 当它跟着 mapSection 存入硬盘时，会被转换为 go_species 信息。
                            //- 以便少存储 一份 go实例，节省 硬盘空间。

    std::vector<std::string> action_names; //- 所有 action实例 都存储在 统一容器中
                            // 其他代码只通过 name／id 来调用它
                            // 每个 go实例，独立拥有一份 action names。
                            // 这样就能 用一种 具象go类（比如橡树）生成不同颜色的 橡树实例。
                            // 此处牵扯到 texture 的动态生成
                            // 在未来可能会 拓展出一个 大模块

    std::vector<Mesh> meshs; //- go实例 与 mesh 是比较静态的关系。
                            // 大部分go不会卸载／增加自己的 mesh实例
                            //- 在一个 具象go类实例 的创建过程中，会把特定的 mesh实例 存入此容器
                            //- 只存储在 mem态。 在go实例存入 硬盘时，mesh实例会被丢弃
                            //- 等再次从section 加载时，再根据 具象go类型，生成新的 mesh实例。
                            
    std::vector<u8>  binary; //- 具象go类 定义的 二进制数据块。真实存储地
                            //- binary 本质是一个 C struct。 由 具象go类方法 使用。
                            //- binary 可能会跟随 go实例 存储到 硬盘态。（未定...）

    //------------ static ----------//
    static ID_Manager  id_manager; //- 负责生产 go_id ( 在.cpp文件中初始化 )

private:
};




#endif

