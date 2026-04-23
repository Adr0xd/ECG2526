#include "clip.h"

/*
 *	 xm,ym                                   xM, ym
 *		----------------------------------------
 *		|                                      |
 *		|                                      |
 *		|                                      |
 *		|                                      |
 *		|                                      |
 *		----------------------------------------
 *    xm,yM                                  xM,YM
 */

namespace egc {
    std::vector<int> computeCSCode(std::vector<vec3> clipWindow, const vec3 p) {
        std::vector<int> code;
        code.resize(4);
        // CODE is UDRL
        //TO DO - compute the code for the point given as argument

        int x_max = clipWindow[0].x;
        int x_min = clipWindow[0].x;
        int y_max = clipWindow[0].y;
        int y_min = clipWindow[0].y;
        for (int i = 1; i < clipWindow.size(); i++) {
            x_max = x_max < clipWindow[i].x ? clipWindow[i].x : x_max;
            y_max = y_max < clipWindow[i].y ? clipWindow[i].y : y_max;

            x_min = x_min > clipWindow[i].x ? clipWindow[i].x : x_min;
            y_min = y_min > clipWindow[i].y ? clipWindow[i].y : y_min;
        }

        code.at(0) = (p.y < y_min); // U
        code.at(1) = (p.y > y_max); // D
        code.at(2) = (p.x > x_max); // R
        code.at(3) = (p.x < x_min); // L

        return code;
    }

    bool simpleRejection(std::vector<int> cod1, std::vector<int> cod2) {
        //TO DO - write the code to determine if the two input codes represent
        //points in the SIMPLE REJECTION case

        for (int i = 0; i < 4; i++)
            if (cod1.at(i) && cod2.at(i))
                return true;
        return false;
    }

    bool simpleAcceptance(std::vector<int> cod1, std::vector<int> cod2) {
        //TO DO - write the code to determine if the two input codes represent
        //points in the SIMPLE ACCEPTANCE case

        return cod1[0] == 0 && cod1[1] == 0 && cod1[2] == 0 && cod1[3] == 0 &&
               cod2[0] == 0 && cod2[1] == 0 && cod2[2] == 0 && cod2[3] == 0;
    }

    //function returns -1 if the line segment cannot be clipped
    int lineClip_CohenSutherland(std::vector<vec3> clipWindow, vec3 &p1, vec3 &p2) {
        float x_max = clipWindow[0].x;
        float x_min = clipWindow[0].x;
        float y_max = clipWindow[0].y;
        float y_min = clipWindow[0].y;

        for (int i = 1; i < clipWindow.size(); i++) {
            x_max = x_max < clipWindow[i].x ? clipWindow[i].x : x_max;
            x_min = x_min > clipWindow[i].x ? clipWindow[i].x : x_min;
            y_max = y_max < clipWindow[i].y ? clipWindow[i].y : y_max;
            y_min = y_min > clipWindow[i].y ? clipWindow[i].y : y_min;
        }

        bool finished = false;
        bool rejected = false;

        do {
            std::vector<int> code1 = computeCSCode(clipWindow, p1);
            const std::vector<int> code2 = computeCSCode(clipWindow, p2);

            const bool reject = simpleRejection(code1, code2);
            if (reject) {
                finished = true;
                rejected = true;
            } else {
                const bool display = simpleAcceptance(code1, code2);
                if (display)
                    finished = true;
                else {
                    if (code1.at(0) == 0 &&
                        code1.at(1) == 0 &&
                        code1.at(2) == 0 &&
                        code1.at(3) == 0) {
                        const vec3 temp = p1;
                        p1 = p2;
                        p2 = temp;
                    }

                    code1 = computeCSCode(clipWindow, p1);

                    if (code1.at(0) == 1) {
                        // U
                        p1.x = p1.x + (p2.x - p1.x) * (y_min - p1.y) / (p2.y - p1.y);
                        p1.y = y_min;
                    } else if (code1.at(1) == 1) {
                        // D
                        p1.x = p1.x + (p2.x - p1.x) * (y_max - p1.y) / (p2.y - p1.y);
                        p1.y = y_max;
                    } else if (code1.at(2) == 1) {
                        // R
                        p1.y = p1.y + (p2.y - p1.y) * (x_max - p1.x) / (p2.x - p1.x);
                        p1.x = x_max;
                    } else if (code1.at(3) == 1) {
                        // L
                        p1.y = p1.y + (p2.y - p1.y) * (x_min - p1.x) / (p2.x - p1.x);
                        p1.x = x_min;
                    }
                }
            }
        } while (!finished);

        if (rejected)
            return -1;

        return 0;
    }

    int lineClip_CyrusBeck(std::vector<vec3> clipWindow, vec3 &p1, vec3 &p2) {
        // ignore nid * d != 0 and then if ni*d <0 PE else PL
        float tE = 0, tL = 1;
        const vec3 p00 = p1;
        const vec3 p11 = p2;

        const vec3 D = p2-p1;

        for (int i = 0; i < clipWindow.size(); i++) {
            const vec3 edgeVector = clipWindow[(i + 1) % clipWindow.size()] - clipWindow[i % clipWindow.size()];

            const vec3 Ni = vec3(edgeVector.y, -edgeVector.x, 0);

            const float prod = dotProduct(Ni, D);

            float ti = -dotProduct(p1-clipWindow[i], Ni)/prod;

            if (prod < 0)
                tE = std::max(tE, ti);
            else
                tL = std::min(tL, ti);
        }

        if (tE>tL) return -1;

        p1 = p00 + (p11-p00)*tE;
        p2 = p00 + (p11-p00)*tL;

        return 0;

    }
}
