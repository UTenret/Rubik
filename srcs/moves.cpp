#include "moves.hpp"

void    updateState(int move) {
    std::string buffer = CubeState;
    if (move == F_PRIME) {
        // face
        buffer[0] = CubeState[2];
        buffer[1] = CubeState[5];
        buffer[2] = CubeState[8];
        buffer[3] = CubeState[1];
        buffer[5] = CubeState[7];
        buffer[6] = CubeState[0];
        buffer[7] = CubeState[3];
        buffer[8] = CubeState[6];
        // first side
        buffer[11] = CubeState[51];
        buffer[14] = CubeState[48];
        buffer[17] = CubeState[45];
        // second side
        buffer[45] = CubeState[29];
        buffer[48] = CubeState[32];
        buffer[51] = CubeState[35];
        // third side
        buffer[29] = CubeState[42];
        buffer[32] = CubeState[39];
        buffer[35] = CubeState[36];
        // last side
        buffer[36] = CubeState[11];
        buffer[39] = CubeState[14];
        buffer[42] = CubeState[17];
    }
    else if (move == F) {
        // face
        buffer[0] = CubeState[6];
        buffer[1] = CubeState[3];
        buffer[2] = CubeState[0];
        buffer[3] = CubeState[7];
        buffer[5] = CubeState[1];
        buffer[6] = CubeState[8];
        buffer[7] = CubeState[5];
        buffer[8] = CubeState[2];
        // first side
        buffer[11] = CubeState[36];
        buffer[14] = CubeState[39];
        buffer[17] = CubeState[42];
        // second side
        buffer[36] = CubeState[35];
        buffer[39] = CubeState[32];
        buffer[42] = CubeState[29];
        // third side
        buffer[29] = CubeState[45];
        buffer[32] = CubeState[48];
        buffer[35] = CubeState[51];
        // last side
        buffer[45] = CubeState[17];
        buffer[48] = CubeState[14];
        buffer[51] = CubeState[11];
    }
    else if (move == U) {
        // face
        buffer[36] = CubeState[38];
        buffer[37] = CubeState[41];
        buffer[38] = CubeState[44];
        buffer[39] = CubeState[37];
        buffer[41] = CubeState[43];
        buffer[42] = CubeState[36];
        buffer[43] = CubeState[39];
        buffer[44] = CubeState[42];
        // first side
        buffer[0] = CubeState[17];
        buffer[1] = CubeState[16];
        buffer[2] = CubeState[15];
        // second side
        buffer[15] = CubeState[18];
        buffer[16] = CubeState[19];
        buffer[17] = CubeState[20];
        // third side
        buffer[18] = CubeState[35];
        buffer[19] = CubeState[34];
        buffer[20] = CubeState[33];
        // last side
        buffer[33] = CubeState[0];
        buffer[34] = CubeState[1];
        buffer[35] = CubeState[2];
    }
    else if (move == U_PRIME) {
        // face
        buffer[36] = CubeState[42];
        buffer[37] = CubeState[39];
        buffer[38] = CubeState[36];
        buffer[39] = CubeState[43];
        buffer[41] = CubeState[37];
        buffer[42] = CubeState[44];
        buffer[43] = CubeState[41];
        buffer[44] = CubeState[38];
        // first side
        buffer[0] = CubeState[33];
        buffer[1] = CubeState[34];
        buffer[2] = CubeState[35];
        // second side
        buffer[15] = CubeState[2];
        buffer[16] = CubeState[1];
        buffer[17] = CubeState[0];
        // third side
        buffer[18] = CubeState[15];
        buffer[19] = CubeState[16];
        buffer[20] = CubeState[17];
        // last side
        buffer[33] = CubeState[20];
        buffer[34] = CubeState[19];
        buffer[35] = CubeState[18];
    }
    else if (move == B_PRIME) {
        // face
        buffer[18] = CubeState[24];
        buffer[19] = CubeState[21];
        buffer[20] = CubeState[18];
        buffer[21] = CubeState[25];
        buffer[23] = CubeState[19];
        buffer[24] = CubeState[26];
        buffer[25] = CubeState[23];
        buffer[26] = CubeState[20];
        // first side
        buffer[47] = CubeState[15];
        buffer[50] = CubeState[12];
        buffer[53] = CubeState[9];
        // second side
        buffer[9] = CubeState[38];
        buffer[12] = CubeState[41];
        buffer[15] = CubeState[44];
        // third side
        buffer[38] = CubeState[33];
        buffer[41] = CubeState[30];
        buffer[44] = CubeState[27];
        // last side
        buffer[27] = CubeState[47];
        buffer[30] = CubeState[50];
        buffer[33] = CubeState[53];
    }
    else if (move == B) {
        // face
        buffer[18] = CubeState[20];
        buffer[19] = CubeState[23];
        buffer[20] = CubeState[26];
        buffer[21] = CubeState[19];
        buffer[23] = CubeState[25];
        buffer[24] = CubeState[18];
        buffer[25] = CubeState[21];
        buffer[26] = CubeState[24];
        // first side
        buffer[38] = CubeState[9];
        buffer[41] = CubeState[12];
        buffer[44] = CubeState[15];
        // second side
        buffer[9] = CubeState[53];
        buffer[12] = CubeState[50];
        buffer[15] = CubeState[47];
        // third side
        buffer[47] = CubeState[27];
        buffer[50] = CubeState[30];
        buffer[53] = CubeState[33];
        // last side
        buffer[27] = CubeState[44];
        buffer[30] = CubeState[41];
        buffer[33] = CubeState[38];
    }
    else if (move == D) {
        // face
        buffer[45] = CubeState[51];
        buffer[46] = CubeState[48];
        buffer[47] = CubeState[45];
        buffer[48] = CubeState[52];
        buffer[50] = CubeState[46];
        buffer[51] = CubeState[53];
        buffer[52] = CubeState[50];
        buffer[53] = CubeState[47];
        // first side
        buffer[6] = CubeState[27];
        buffer[7] = CubeState[28];
        buffer[8] = CubeState[29];
        // second side
        buffer[27] = CubeState[26];
        buffer[28] = CubeState[25];
        buffer[29] = CubeState[24];
        // third side
        buffer[24] = CubeState[9];
        buffer[25] = CubeState[10];
        buffer[26] = CubeState[11];
        // last side
        buffer[9] = CubeState[8];
        buffer[10] = CubeState[7];
        buffer[11] = CubeState[6];
    }
    else if (move == D_PRIME) {
        // face
        buffer[45] = CubeState[47];
        buffer[46] = CubeState[50];
        buffer[47] = CubeState[53];
        buffer[48] = CubeState[46];
        buffer[50] = CubeState[52];
        buffer[51] = CubeState[45];
        buffer[52] = CubeState[48];
        buffer[53] = CubeState[51];
        // first side
        buffer[6] = CubeState[11];
        buffer[7] = CubeState[10];
        buffer[8] = CubeState[9];
        // second side
        buffer[27] = CubeState[6];
        buffer[28] = CubeState[7];
        buffer[29] = CubeState[8];
        // third side
        buffer[24] = CubeState[29];
        buffer[25] = CubeState[28];
        buffer[26] = CubeState[27];
        // last side
        buffer[9] = CubeState[24];
        buffer[10] = CubeState[25];
        buffer[11] = CubeState[26];
    }
    else if (move == L) {
        // face
        buffer[27] = CubeState[29];
        buffer[28] = CubeState[32];
        buffer[29] = CubeState[35];
        buffer[30] = CubeState[28];
        buffer[32] = CubeState[34];
        buffer[33] = CubeState[27];
        buffer[34] = CubeState[30];
        buffer[35] = CubeState[33];
        // first side
        buffer[0] = CubeState[44];
        buffer[3] = CubeState[43];
        buffer[6] = CubeState[42];
        // second side
        buffer[42] = CubeState[18];
        buffer[43] = CubeState[21];
        buffer[44] = CubeState[24];
        // third side
        buffer[18] = CubeState[53];
        buffer[21] = CubeState[52];
        buffer[24] = CubeState[51];
        // last side
        buffer[51] = CubeState[0];
        buffer[52] = CubeState[3];
        buffer[53] = CubeState[6];
    }
    else if (move == L_PRIME) {
        // face
        buffer[27] = CubeState[33];
        buffer[28] = CubeState[30];
        buffer[29] = CubeState[27];
        buffer[30] = CubeState[34];
        buffer[32] = CubeState[28];
        buffer[33] = CubeState[35];
        buffer[34] = CubeState[32];
        buffer[35] = CubeState[29];
        // first side
        buffer[0] = CubeState[51];
        buffer[3] = CubeState[52];
        buffer[6] = CubeState[53];
        // second side
        buffer[42] = CubeState[6];
        buffer[43] = CubeState[3];
        buffer[44] = CubeState[0];
        // third side
        buffer[18] = CubeState[42];
        buffer[21] = CubeState[43];
        buffer[24] = CubeState[44];
        // last side
        buffer[51] = CubeState[24];
        buffer[52] = CubeState[21];
        buffer[53] = CubeState[18];
    }
    else if (move == R) {
        // face
        buffer[9] = CubeState[15];
        buffer[10] = CubeState[12];
        buffer[11] = CubeState[9];
        buffer[12] = CubeState[16];
        buffer[14] = CubeState[10];
        buffer[15] = CubeState[17];
        buffer[16] = CubeState[14];
        buffer[17] = CubeState[11];
        // first side
        buffer[2] = CubeState[45];
        buffer[5] = CubeState[46];
        buffer[8] = CubeState[47];
        // second side
        buffer[45] = CubeState[26];
        buffer[46] = CubeState[23];
        buffer[47] = CubeState[20];
        // third side
        buffer[20] = CubeState[36];
        buffer[23] = CubeState[37];
        buffer[26] = CubeState[38];
        // last side
        buffer[36] = CubeState[8];
        buffer[37] = CubeState[5];
        buffer[38] = CubeState[2];
    }
    else if (move == R_PRIME) {
        // face
        buffer[9] = CubeState[11];
        buffer[10] = CubeState[14];
        buffer[11] = CubeState[17];
        buffer[12] = CubeState[10];
        buffer[14] = CubeState[16];
        buffer[15] = CubeState[9];
        buffer[16] = CubeState[12];
        buffer[17] = CubeState[15];
        // first side
        buffer[2] = CubeState[38];
        buffer[5] = CubeState[37];
        buffer[8] = CubeState[36];
        // second side
        buffer[36] = CubeState[20];
        buffer[37] = CubeState[23];
        buffer[38] = CubeState[26];
        // third side
        buffer[20] = CubeState[47];
        buffer[23] = CubeState[46];
        buffer[26] = CubeState[45];
        // last side
        buffer[45] = CubeState[2];
        buffer[46] = CubeState[5];
        buffer[47] = CubeState[8];
    }
    CubeState = buffer;
}
