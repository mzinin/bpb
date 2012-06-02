#include "monom64.h"

void Monom64::Init() {
  mDimIndepend = mIndepend->dim();
  for (int i=0; i<64; i++) {
    One[i] = 1;
    One[i] = One[i] << i;
    Zero[i] = ~One[i];
  }

  degrees[0] = 0; degrees[1] = 1; degrees[2] = 1; degrees[3] = 2;
  degrees[4] = 1; degrees[5] = 2; degrees[6] = 2; degrees[7] = 3;
  degrees[8] = 1; degrees[9] = 2; degrees[10] = 2; degrees[11] = 3;
  degrees[12] = 2; degrees[13] = 3; degrees[14] = 3; degrees[15] = 4;
  degrees[16] = 1; degrees[17] = 2; degrees[18] = 2; degrees[19] = 3;
  degrees[20] = 2; degrees[21] = 3; degrees[22] = 3; degrees[23] = 4;
  degrees[24] = 2; degrees[25] = 3; degrees[26] = 3; degrees[27] = 4;
  degrees[28] = 3; degrees[29] = 4; degrees[30] = 4; degrees[31] = 5;
  degrees[32] = 1; degrees[33] = 2; degrees[34] = 2; degrees[35] = 3;
  degrees[36] = 2; degrees[37] = 3; degrees[38] = 3; degrees[39] = 4;
  degrees[40] = 2; degrees[41] = 3; degrees[42] = 3; degrees[43] = 4;
  degrees[44] = 3; degrees[45] = 4; degrees[46] = 4; degrees[47] = 5;
  degrees[48] = 2; degrees[49] = 3; degrees[50] = 3; degrees[51] = 4;
  degrees[52] = 3; degrees[53] = 4; degrees[54] = 4; degrees[55] = 5;
  degrees[56] = 3; degrees[57] = 4; degrees[58] = 4; degrees[59] = 5;
  degrees[60] = 4; degrees[61] = 5; degrees[62] = 5; degrees[63] = 6;
  degrees[64] = 1; degrees[65] = 2; degrees[66] = 2; degrees[67] = 3;
  degrees[68] = 2; degrees[69] = 3; degrees[70] = 3; degrees[71] = 4;
  degrees[72] = 2; degrees[73] = 3; degrees[74] = 3; degrees[75] = 4;
  degrees[76] = 3; degrees[77] = 4; degrees[78] = 4; degrees[79] = 5;
  degrees[80] = 2; degrees[81] = 3; degrees[82] = 3; degrees[83] = 4;
  degrees[84] = 3; degrees[85] = 4; degrees[86] = 4; degrees[87] = 5;
  degrees[88] = 3; degrees[89] = 4; degrees[90] = 4; degrees[91] = 5;
  degrees[92] = 4; degrees[93] = 5; degrees[94] = 5; degrees[95] = 6;
  degrees[96] = 2; degrees[97] = 3; degrees[98] = 3; degrees[99] = 4;
  degrees[100] = 3; degrees[101] = 4; degrees[102] = 4; degrees[103] = 5;
  degrees[104] = 3; degrees[105] = 4; degrees[106] = 4; degrees[107] = 5;
  degrees[108] = 4; degrees[109] = 5; degrees[110] = 5; degrees[111] = 6;
  degrees[112] = 3; degrees[113] = 4; degrees[114] = 4; degrees[115] = 5;
  degrees[116] = 4; degrees[117] = 5; degrees[118] = 5; degrees[119] = 6;
  degrees[120] = 4; degrees[121] = 5; degrees[122] = 5; degrees[123] = 6;
  degrees[124] = 5; degrees[125] = 6; degrees[126] = 6; degrees[127] = 7;
  degrees[128] = 1; degrees[129] = 2; degrees[130] = 2; degrees[131] = 3;
  degrees[132] = 2; degrees[133] = 3; degrees[134] = 3; degrees[135] = 4;
  degrees[136] = 2; degrees[137] = 3; degrees[138] = 3; degrees[139] = 4;
  degrees[140] = 3; degrees[141] = 4; degrees[142] = 4; degrees[143] = 5;
  degrees[144] = 2; degrees[145] = 3; degrees[146] = 3; degrees[147] = 4;
  degrees[148] = 3; degrees[149] = 4; degrees[150] = 4; degrees[151] = 5;
  degrees[152] = 3; degrees[153] = 4; degrees[154] = 4; degrees[155] = 5;
  degrees[156] = 4; degrees[157] = 5; degrees[158] = 5; degrees[159] = 6;
  degrees[160] = 2; degrees[161] = 3; degrees[162] = 3; degrees[163] = 4;
  degrees[164] = 3; degrees[165] = 4; degrees[166] = 4; degrees[167] = 5;
  degrees[168] = 3; degrees[169] = 4; degrees[170] = 4; degrees[171] = 5;
  degrees[172] = 4; degrees[173] = 5; degrees[174] = 5; degrees[175] = 6;
  degrees[176] = 3; degrees[177] = 4; degrees[178] = 4; degrees[179] = 5; 
  degrees[180] = 4; degrees[181] = 5; degrees[182] = 5; degrees[183] = 6;
  degrees[184] = 4; degrees[185] = 5; degrees[186] = 5; degrees[187] = 6;
  degrees[188] = 5; degrees[189] = 6; degrees[190] = 6; degrees[191] = 7;
  degrees[192] = 2; degrees[193] = 3; degrees[194] = 3; degrees[195] = 4;
  degrees[196] = 3; degrees[197] = 4; degrees[198] = 4; degrees[199] = 5;
  degrees[200] = 3; degrees[201] = 4; degrees[202] = 4; degrees[203] = 5;
  degrees[204] = 4; degrees[205] = 5; degrees[206] = 5; degrees[207] = 6;
  degrees[208] = 3; degrees[209] = 4; degrees[210] = 4; degrees[211] = 5;
  degrees[212] = 4; degrees[213] = 5; degrees[214] = 5; degrees[215] = 6;
  degrees[216] = 4; degrees[217] = 5; degrees[218] = 5; degrees[219] = 6;
  degrees[220] = 5; degrees[221] = 6; degrees[222] = 6; degrees[223] = 7;
  degrees[224] = 3; degrees[225] = 4; degrees[226] = 4; degrees[227] = 5;
  degrees[228] = 4; degrees[229] = 5; degrees[230] = 5; degrees[231] = 6;
  degrees[232] = 4; degrees[233] = 5; degrees[234] = 5; degrees[235] = 6;
  degrees[236] = 5; degrees[237] = 6; degrees[238] = 6; degrees[239] = 7;
  degrees[240] = 4; degrees[241] = 5; degrees[242] = 5; degrees[243] = 6;
  degrees[244] = 5; degrees[245] = 6; degrees[246] = 6; degrees[247] = 7;
  degrees[248] = 5; degrees[249] = 6; degrees[250] = 6; degrees[251] = 7;
  degrees[252] = 6; degrees[253] = 7; degrees[254] = 7; degrees[255] = 8;
}

int Monom64::compare(const Monom64& a, const Monom64& b) const {
  Monom64 tmp(a);
  tmp.mult(b);
  return compare(tmp);
}

std::istream& operator>>(std::istream& in, Monom64& a) {
  std::streampos posbeg = in.tellg();
  int var = a.mIndepend->read(in);
  if (var < 0) {
    in.clear();
    in.setstate(std::ios::failbit);
  }
  else {
    a.setZero();
    int deg;
    do {
      deg = 1;
      std::streampos posbeg = in.tellg();
      if ((in >> std::ws).peek() == '^') {
        in.get();
        in >> std::ws >> deg;
        if (in.fail() || deg < 0) {
          in.setstate(std::ios::failbit);
          IMESSAGE("expected 'degree >= 0'");
        }
      }
      a.prolong(var,deg);
         
      posbeg = in.tellg();
      if (in.peek() != '*')
        var = -1;
      else {
        in.get();
        var = a.mIndepend->read(in);
        if (var < 0) {
          in.clear();
          in.seekg(posbeg);
        }
      }
    } while(var >= 0);
    if (in.eof() &&
        deg >= 0)
      in.clear();
  }
  return in;
}

std::ostream& operator<<(std::ostream& out, const Monom64& a) {
  if (a.degree() == 0)
    out << '1';
  else {
    int i = 0;
    IVariables::ConstIterator j(a.mIndepend->begin());
    while(a.deg(i) == 0) {
      ++i;
      ++j;
    }
    out << *j;
    if (a.deg(i) > 1)
      out << '^' << a[i];
    ++i;
    ++j;
    while(j!=a.mIndepend->end()){
      if (a.deg(i)) {
        out << '*' << *j;
        if (a.deg(i) > 1)
          out << '^' << a[i];
      }
      ++i;
      ++j;
    }
  }
  return out;
}

IVariables* Monom64::mIndepend = new IVariables();
IAllocator Monom64::sAllocator(sizeof(Monom64));
unsigned long long Monom64::Zero[64], Monom64::One[64];
unsigned long long Monom64::degrees[256];
int Monom64::mDimIndepend;
