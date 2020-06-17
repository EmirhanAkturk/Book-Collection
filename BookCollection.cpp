#include <string>
#include <iostream>


using namespace std;

class Item
{
public:
	Item(const string& name, int count = 1){
        this->name=name;
        this->count=count;
    }
    Item():name{" "},count{0} {}
    Item(const Item &book){
        name=book.name;
        count=book.count;
    }
	int count;   // Kitaptan kac adet oldugunu tutar // Holds the number of the item
	string name; // Kitabın adını tutar // Holds the name of the book
};

class BookCollection
{
	
	friend ostream& operator<<(ostream & out, const BookCollection & collection){

        for(int i{0};i<collection.numberOfUniqueItems;++i)
            out<<"Book name:"<<collection.items[i].name<<" count:"<<collection.items[i].count<<endl;
        
        return out;
    }
public:
	BookCollection():numberOfUniqueItems{0},items{nullptr} { } // empty collection/ bos koleksiyon -> [5 puan/points]
    
	BookCollection(const string & bookname){
        
      
        numberOfUniqueItems=1;
        items=new Item[numberOfUniqueItems];
        if(items==nullptr)
            throw (-1);
        
        items[0]=Item{bookname};

        
    }

	BookCollection(const Item& item){
        
        //cout<<"Item conversion constructor"<<endl;
        numberOfUniqueItems=1;
        items=new Item[numberOfUniqueItems];
        if(items==nullptr)
            throw (-1);
        
        items[0]=item;

    } 
    ~BookCollection(){
        
        if(items!=nullptr){
            delete[] items;
            items=nullptr;}
        
    }
		
        
    BookCollection(BookCollection& otherCollection):numberOfUniqueItems{otherCollection.numberOfUniqueItems}
    {
        
        items=new Item[numberOfUniqueItems];
        
        if(items==nullptr)
            throw(-1);

        for(int i{0};i<numberOfUniqueItems;++i)
            items[i]=otherCollection.items[i];
        
    }


		
    BookCollection(BookCollection&& otherCollection)
    :numberOfUniqueItems{otherCollection.numberOfUniqueItems},items{otherCollection.items}
    {
        cout<<"Move constructer"<<endl;
        otherCollection.numberOfUniqueItems=0;
        otherCollection.items=nullptr;
    }


    BookCollection & operator=(const BookCollection & otherCollection){
        cout<<"copy assignmet"<<endl;
        if(this!= &otherCollection){//selt assignmet check
            if(items!=nullptr) 
                delete[] items;
            
            numberOfUniqueItems=otherCollection.numberOfUniqueItems;
            items=new Item[numberOfUniqueItems];
            if(items==nullptr)
                throw(-1);
            
            for(int i{0};i<numberOfUniqueItems;++i)
                items[i]=otherCollection.items[i];
        }
        
        return *this;
    }


		
    BookCollection & operator=(BookCollection &&otherCollection){
        cout << "Move Assignment" << endl;

        if(this==&otherCollection)//self assignmet check
            return *this;

        if(items!=nullptr)
            delete[] items;

        numberOfUniqueItems=otherCollection.numberOfUniqueItems;
        items=otherCollection.items;

        otherCollection.items=nullptr;
        otherCollection.numberOfUniqueItems=0;
        return *this;
    }

		
	bool operator!() const{
        return numberOfUniqueItems==0;
    } 
	
    bool operator==(const BookCollection & otherCollection)const{
        if(numberOfUniqueItems!=otherCollection.numberOfUniqueItems)
            return false;

        for(int i{0};i<numberOfUniqueItems;++i)
            if(!(items[i].name.compare(otherCollection.items[i].name)==0))//item isimleri aynı mı diye kontrol eder
                return false;
        return true;
    }

    bool operator!=(const BookCollection & otherCollection)const{
        return !(*this==otherCollection);
    }

    bool operator>(const BookCollection & otherCollection)const{
        int thisCount=0,otherCount=0;
        for(int i{0};i<numberOfUniqueItems;++i)
            thisCount+=items[i].count;

        for(int i{0};i<otherCollection.numberOfUniqueItems;++i)
            otherCount+=otherCollection.items[i].count;
        
        return (thisCount>otherCount);
    }

    bool operator>=(const BookCollection & otherCollection)const{
        return (*this>otherCollection && *this==otherCollection);
    }

    bool operator<=(const BookCollection &otherCollection)const{
        return !(*this>otherCollection);
    }

    bool operator<(const BookCollection &otherCollection)const{
        return !(*this>=otherCollection);
    }


	BookCollection& operator+=(const BookCollection& otherCollection){
        int tempUniqueItems=numberOfUniqueItems+otherCollection.numberOfUniqueItems;//max duruma göre alan ayırıldı
        int isFind;

        Item *tempItems=new Item[tempUniqueItems];
        if(tempItems==nullptr)
            throw(-1);

        for(int i{0};i<numberOfUniqueItems;++i)
            tempItems[i]=items[i];
        
        
        for(int i{0};i<otherCollection.numberOfUniqueItems;++i){
            isFind=0;
            for(int j{0};j<numberOfUniqueItems;++j){//eklenecek item collection içinde var mı diye kontrol eder
                if(otherCollection.items[i].name.compare(tempItems[j].name)==0){
                    tempItems[j].count+=otherCollection.items[i].count;//item zaten varsa count arttırılır
                    isFind=1;
                    break;}
            }
            if(!isFind){//item collection içinde yoksa eklenir
                tempItems[numberOfUniqueItems++]=otherCollection.items[i];
            }
        }

        if(items!=nullptr)
            delete[] items;

        if(numberOfUniqueItems==tempUniqueItems){//Eger tempItems icin ayırdıgımız alan tamamen dolduysa yeni Items olarak ata
            items=tempItems;
            return *this;
        }

        //Eger basta ayrılan alan fazlaysa içindekileri yeni alana kopyala ve başta ayrılan alanı sil
        items=new Item[numberOfUniqueItems];

        for(int i{0};i<numberOfUniqueItems;++i)
            items[i]=tempItems[i];
        
        if(tempItems!=nullptr)
            delete[] tempItems;
        
        return *this;
    }

	BookCollection& operator-=(const Item& item){
        
        for(int i{0};i<numberOfUniqueItems;++i){//silinecek item collection içinde var mı diye kontrol eder
            if(items[i].name.compare(item.name)==0){
                items[i].count-=item.count;//item zaten varsa count arttırılır
                if(items[i].count<1)//yeterli item kalmadıysa collectiondan silinir
                {
                    for(int j{i};j<numberOfUniqueItems;j++)//silinecegi için shifting yapılır
                        items[j]=items[j+1];
                    
                    --numberOfUniqueItems;
                }
                
                return *this;//istilen islem tamamlandıgı icin donguden cikilir
            }            
        }

        return *this;
    } 


private:
	// numberOfUniqueItems koleksiyondaki Item sayısını tutar, TOPLAM ÖĞE SAYISINI değil
	// numberOfUniqueItems holds unique items not the total number of items in the collection
	int numberOfUniqueItems=0;
	Item * items;

	
};

int main(){

    Item book{"Korku Vadisi"};
    BookCollection collection{book};
    BookCollection collection2{"Korku Vadisi"};
    BookCollection collection3{"Arsen Lupen"};  
    BookCollection collection4{"Arsen Lupen"};  
    BookCollection collection5{"Kızıl Dosya"};  

    Item book2{"Korku Vadisi"};
    Item book3{"Arsen Lupen"};
    Item book4{"Olasılıksız"};

    cout<<"Collection:"<<collection<<endl;
    cout<<"###########################"<<endl;
    collection+=collection2;
    collection+=collection3;
    collection+=collection4;
    collection+=collection5;

    cout<<"Collection:"<<collection<<endl;
    cout<<"###########################"<<endl;
    collection2=collection;

    cout<<"Collection2:"<<collection2<<endl;
    cout<<"###########################"<<endl;
    collection2-=book;
    collection2-=book2;
    collection2-=book3;
    
    collection5=collection3;
    collection2+=collection5;
    
    cout<<"Collection2:"<<collection2<<endl;


    return 0;
}
