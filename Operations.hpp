#pragma once
//#TODO decidir quais parametros precisam ter as funcoes das operaçoes

//Access
void LDA();
void LDX();
void LDY();
void STA();
void STX();
void STY();

//Arithmetic
void ADC();
void DEC();
void DEX();
void DEY();
void INC();
void INX();
void INY();
void SBC();

//Bitwise
void AND();
void BIT();
void EOR();
void ORA();

//Branch
void BCC();
void BCS();
void BEQ();
void BNE();
void BMI();
void BPL();
void BVC();
void BVS();


//Compare
void CMP();
void CPX();
void CPY();

//Flags
void CLC();
void CLD();
void CLI();
void CLV();
void SEC();
void SED();
void SEI();

//Jump
void BRK();
void JMP();
void JSR();
void RTI();
void RTS();

//Stack
void PHA();
void PHP();
void PLA();
void PLP();
void TSX();
void TXS();


//Transfer
void TAX();
void TAY();
void TXA();
void TXY();
void TYA();

//Shift
void ASL();
void LSR();
void ROL();
void ROR();

//Other
void NOP();