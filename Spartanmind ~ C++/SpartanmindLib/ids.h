/**
 * @file ids.h
 * @author Aditya Menon
 *
 * ID values for the Spartamind game.
 */

#ifndef MAHJONG_SPARTANMIND_IDS_H
#define MAHJONG_SPARTANMIND_IDS_H

/**
 * IDs for the Spartamind game.
 */
enum IDs {
    IDM_SOLVE = wxID_HIGHEST + 1,
    IDM_LEVEL0 = IDM_SOLVE + 1,
    IDM_LEVEL1 = IDM_LEVEL0 + 1,
    IDM_LEVEL2 = IDM_LEVEL1 + 1,
    IDM_LEVEL3 = IDM_LEVEL2 + 1,
    IDM_HINT = IDM_LEVEL3 + 1,
};

#endif //MAHJONG_SPARTANMIND_IDS_H 