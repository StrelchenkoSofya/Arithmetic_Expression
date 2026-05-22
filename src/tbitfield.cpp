// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);

TBitField::TBitField(int len)
{
    if (len <= 0) throw "negativeLen";
    BitLen = len;
    int size = sizeof(TELEM) * 8;
    MemLen = (BitLen + size  - 1) >> sz;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = 0;
    }
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField()
{
    delete[]pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    if (n < 0) throw "negativeIndex";
    return n >> sz;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    if (n < 0) throw "negativeIndex";
    int size = sizeof(TELEM) * 8;
    return 1 << (n - this->GetMemIndex(n) * size);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n < 0) throw "negativeIndex";
    if (n > this->BitLen) throw "tooLargeIndex";
    int ind = this->GetMemIndex(n);
    TELEM t = this->GetMemMask(n);
    this->pMem[ind] |= t;
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n < 0) throw "negativeIndex";
    if (n > this->BitLen) throw "tooLargeIndex";
    int ind = this->GetMemIndex(n);
    TELEM t = ~(this->GetMemMask(n));
    this->pMem[ind] &= t;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n < 0) throw "negativeIndex";
    if (n > this->BitLen) throw "tooLargeIndex";
    int ind = this->GetMemIndex(n);
    TELEM t = this->GetMemMask(n);
    return this->pMem[ind] & t;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (this == &bf) return *this;
    delete[]pMem;
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = bf.pMem[i];
    }
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (this->BitLen != bf.BitLen) {
        return 0;
  }
    for (int i = 0; i < this->MemLen; i++) {
        if (this->pMem[i] != bf.pMem[i]) {
            return 0;
        }
    }
    return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    return !(*this == bf);
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    TBitField t = TBitField(max(this->BitLen, bf.BitLen));
    int mn = min(this->MemLen, bf.MemLen);
    for (int i = 0; i < mn; i++) {
        t.pMem[i] = this->pMem[i] | bf.pMem[i];
    }
    if (this->MemLen > bf.MemLen) {
        for (int i = mn; i < this->MemLen; i++) {
            t.pMem[i] = this->pMem[i];
        }
    }
    if (this->MemLen < bf.MemLen) {
        for (int i = mn; i < bf.MemLen; i++) {
            t.pMem[i] = bf.pMem[i];
        }
    }
    return t;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    TBitField t = TBitField(max(this->BitLen, bf.BitLen));
    int mn = min(this->MemLen, bf.MemLen);
    for (int i = 0; i < mn; i++) {
        t.pMem[i] = this->pMem[i] & bf.pMem[i];
    }
    return t;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField t = TBitField(this->BitLen);
    for (int i = 0; i < this->MemLen; i++) {
        t.pMem[i] = ~(this->pMem[i]);
    }
    TELEM mask = 0;
    for (int i = 0; i < sizeof(TELEM) * 8; i++) {
        mask |= this->GetMemMask(i);
    }
    mask = mask >> (sizeof(TELEM) * 8 * MemLen - BitLen);
    t.pMem[MemLen - 1] &= mask;
    return t;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    for (int i = 0; i < bf.MemLen; i++) {
        istr >> bf.pMem[i];
    }
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = 0; i < bf.MemLen; i++) {
        ostr << bf.pMem[i];
    }
    return ostr;
}
