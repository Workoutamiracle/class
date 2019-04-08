#include <iostream>
#include <string>

using namespace std;
class Quote{
private:
    string book;
protected:
    double price;
public:
    Quote() = default;
    Quote(double num,const string &name) : book(name),price(num) {}
    string isbn() const{ return book; }
    virtual double net_price(size_t n) const { return n*price; };
    virtual string debug() const { return book+" "+to_string(price);}
};
class Bulk_quote : public Quote{
protected:
    size_t min_qty = 0;
    double discount = 0.0;
public:
    Bulk_quote() = default;
    Bulk_quote(double num,const string &name,size_t n,double dc) : Quote(num,name),min_qty(n),discount(dc) {  }
    double net_price(size_t n) const override;
    string debug() const override { return Quote::debug()+" "+to_string(min_qty)+" "+to_string(discount); }
};
class Limit_quote : public Bulk_quote{
public:
    Limit_quote() = default;
    Limit_quote(double num,const string &name,size_t n,double dc) : Bulk_quote(num,name,n,dc){}
    double net_price(size_t n) const override;
    string debug() const override { return Bulk_quote::debug();}

};

double Bulk_quote::net_price(size_t n) const
{
    if(n >= min_qty)
        return n*(1-discount)*price;
    else
        return n*price;
}

double Limit_quote::net_price(size_t n) const
{
    if(n <= min_qty)
        return n*(1-discount)*price;
    else
        return n*price;
}
double print_total(ostream &os,const Quote &item,size_t n)
{
    double ret = item.net_price(n);
    os << "ISBN: " << item.isbn() << " #sold: " << n << " total due: " << ret << endl;
    return ret;
}

class Disc_quote : public Quote{
protected:
    size_t quantity = 0;
    double discount = 0.0;
public:
    Disc_quote() = default;
    Disc_quote(const string &book,double price,size_t qty,double dc) : Quote(price,book),quantity(qty),discount(dc) {  }
    double net_price(size_t n)const = 0;
};

class Bulk_quote2 : public Disc_quote{
public:
    Bulk_quote2() = default;
    Bulk_quote2(const string &book,double price,size_t qty,double dc) : Disc_quote(book,price,qty,dc) {  }
    double net_price(size_t n)const override;
};
double Bulk_quote2::net_price(size_t n)const
{
    if(n >= quantity)
        return n*(1-discount)*price;
    else
        return n*price;
}
int main()
{
    Bulk_quote2 bq2("wh",10,10,0.2);
    cout << bq2.Quote::net_price(10) << endl;
    cout << bq2.net_price(10) << endl;
    return 0;
}

