#pragma once

// 传入参数均为 BinNode<T> x（除 sibling 传入类型为 BinNodePosi<T> p）

/* BinNode状态与性质的判断 */
#define IsRoot(x) ( ! ( (x).parent ) ) // 是否为根节点
#define IsLChild(x) ( ( ! IsRoot(x) ) && ( ( & (x) ) == (x).parent->lc ) ) // 是否为左孩子（&为取地址运算符）
#define IsRChild(x) ( ( ! IsRoot(x) ) && ( ( & (x) ) == (x).parent->rc ) ) // 是否为右孩子
#define HasParent(x) ( ! IsRoot(x) )
#define HasLChild(x) ( (x).lc )
#define HasRChild(x) ( (x).rc )
#define HasChild(x) ( HasLChild(x) || HasRChild(x) )     // 至少拥有一个孩子
#define HasBothChild(x) ( HasLChild(x) && HasRChild(x) ) // 同时拥有两个孩子
#define IsLeaf(x) ( ! HasChild(x) ) // 是否为叶子节点

/* 与BinNode具有特定关系的节点及指针 */
#define sibling(p) ( IsLChild( * (p) ) ? (p)->parent->rc : (p)->parent->lc ) // 兄弟，亦即二叉树中同根的另一孩子（*为解引用运算符）
#define uncle(x) ( sibling( (x)->parent ) ) // 叔叔，亦即父节点的兄弟
#define FromParentTo(x) ( IsRoot(x) ? _root : ( IsLChild(x) ? (x).parent->lc : (x).parent->rc ) ) // 来自父节点的引用