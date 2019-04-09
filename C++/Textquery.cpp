#include <iostream>
#include <memory>

using namespace std;

class QueryResult{

};
class TextQuery{
public:
    size_t line_no;
};
class Query;

class Query_base{
    friend Query;
protected:
    //using line_no = TextQuery::line_no;
private:
    //virtual QueryResult eval(const TextQuery&)const=0;
    virtual string rep() const=0;
};

class WordQuery : public Query_base{
    friend class Query;
    WordQuery(const string &s) : query_word(s) { cout << s+"WordQuery" << endl; }
    //QueryResult eval(const TextQuery &t)const;
    string rep() const { return query_word; }
    string query_word;
};

class Query{
    friend Query operator~(const Query &);
    friend Query operator&(const Query &,const Query &);
    friend Query operator|(const Query &,const Query &);
public:
    Query(const string &);
    //QuertResult eval(const TextQuery &)const;
    string rep() const {return q->rep();}
private:
    Query(shared_ptr<Query_base> query) : q(query) {   cout <<q->rep()+"Query(shared_ptr)" << endl; }
    shared_ptr<Query_base> q;
};

ostream &operator <<(ostream &os,const Query &query)
{
    return os << query.rep();
}

Query::Query(const string &s) : q(new WordQuery(s)) { cout << s+"Query" << endl;  }

class NotQuery : public Query_base{
    friend Query operator~(const Query &);
    NotQuery(const Query &q) : query(q) {  cout << q.rep()+"NotQuery" << endl;  }
    string rep() const { return "~("+query.rep()+")"; }
    //QuertResult eval(const TextQuery &)const;
    Query query;
};

Query operator~(const Query &q)
{
    return shared_ptr<Query_base>(new NotQuery(q));
}

class BinaryQuery : public Query_base{
protected:
    BinaryQuery(const Query &l,const Query &r,string s) : lhs(l),rhs(r),opSym(s) {  cout << s+"BinaryQuery" << endl;  }
    string rep() const { return "("+lhs.rep()+" "+opSym+" "+rhs.rep()+" "+")"; }
    Query lhs,rhs;
    string opSym;
};

class AndQuery : public BinaryQuery{
    friend Query operator&(const Query &,const Query &);
    AndQuery(const Query &left,const Query &right) : BinaryQuery(left,right,"&") {   cout << "AndQuery" << endl; }
    //QuertResult eval(const TextQuery &)const;
};

Query operator&(const Query &l,const Query &r)
{
    return shared_ptr<Query_base>(new AndQuery(l,r));
}

class OrQuery : public BinaryQuery{
    friend Query operator|(const Query &,const Query &);
    OrQuery(const Query &left,const Query &right) : BinaryQuery(left,right,"|") {   cout << "OrQuery" << endl; }
    //QuertResult eval(const TextQuery &)const;
};

Query operator|(const Query &l,const Query &r)
{
    return shared_ptr<Query_base>(new OrQuery(l,r));
}

int main()
{
    Query q = Query("1") & Query("2") | Query("3");
    cout << q << endl;
    return 0;
}

