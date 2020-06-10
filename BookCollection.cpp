#include <string>
#include <iostream>


using namespace std;

class Item
{
public:
	// Verilen parametrelere uygun şekilde yeni bir item nesnesi oluşturur [5 Puan]
	// Constructs a new Item object accoring to the given parameters [5 points]
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
	/* Koleksiyonda bulunan tum ogeleri ekrana bastirin [5 Puan]
	   (iomanip, vb.) ek kutuphaneler yardimiyla tablo şeklinde bir gorunum olusturun [5 Ek Puan]*/

	   /* prints all the items in the collection [5 point]
		   use extra libraries (iomanip, etc.) to create a table view [5 points extra]	*/
	friend ostream& operator<<(ostream & out, const BookCollection & collection){

        for(int i{0};i<collection.numberOfUniqueItems;++i)
            out<<"Book name:"<<collection.items[i].name<<" count:"<<collection.items[i].count<<endl;
        
        return out;
    }
public:
	BookCollection():numberOfUniqueItems{0},items{nullptr} { } // empty collection/ bos koleksiyon -> [5 puan/points]
    
	// 1 item of bookname [5 points] 
	// verilen kitap isminden tek kitap iceren bir koleksiyon olusturur [5 puan]
	BookCollection(const string & bookname){
        
        //cout<<"string conversion constructor"<<endl;
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

    } // creates a collection of 1 item given -> 5 points

	/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		ASAGI EKSIK OLAN PROTOTOPLERI TAMAMLAYINIZ!!!
		COMPLETE THE MISSING FUNCTION PROTOTYPES BELOW!!!
		!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
		
        //  Write a destructor [5 points]
		//  Yikici fonksiyon [5 Puan]
    ~BookCollection(){
        
        //cout<<"Destructor\n";
        if(items!=nullptr){
            delete[] items;
            items=nullptr;}
        
    }
		
        // Write a copy constructor -> 10 points
		// Kopya Yapici [10 Puan]
    BookCollection(BookCollection& otherCollection):numberOfUniqueItems{otherCollection.numberOfUniqueItems}
    {
        //cout<<"Copy constructer"<<endl;
        
        items=new Item[numberOfUniqueItems];
        
        if(items==nullptr)
            throw(-1);

        for(int i{0};i<numberOfUniqueItems;++i)
            items[i]=otherCollection.items[i];
        
    }


		// Write a move constructor -> 10 points
		// Tasiyici Yapici [10 puan]
    BookCollection(BookCollection&& otherCollection)
    :numberOfUniqueItems{otherCollection.numberOfUniqueItems},items{otherCollection.items}
    {
        cout<<"Move constructer"<<endl;
        otherCollection.numberOfUniqueItems=0;
        otherCollection.items=nullptr;
    }


		// Overload copy assignment operator -> 10 points
		// Kopyalayici Atama Operatorunu asırı yukleyin [10 Puan]
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


		// Overload move assignment operator -> 10 points
		// Tasıyıcı Atama Operatorunu asırı yukleyin [10 Puan]
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

		// Koleksiyon bossa true, degilse false dondurur
		// ! operator returns true if the collection is empty and it results false otherwise.
	bool operator!() const{
        return numberOfUniqueItems==0;
    } // [3 puan/points]


	/* ==, != , >, <, >= ve <= operatorlerini asırı yukleyin
	   Bu operatorler Koleksiyon icindeki TOPLAM OGE sayisina gore karsılastırma yaparlar.
	   Tum operatorleri dogru yapanlar [22 Puan], diger durumda operator basına [3 Puan]  */
	   /* Overload ==, != , >, <, >= and <= operators
		  These operators compare the TOTAL NUMBER OF ITEMS (counts of all items) in the collections
		  Total points of comparison operators
		  (6 operators = 22 points, less than 6 operators each operator is 3 points)*/
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




    /* İki koleksiyonu birleştiren += operatorünü aşırı yükleyiniz [25 Puan]
			 Eğer bir öğe mevcut koleksiyonda yoksa o öğeyi ekleyin,
			 eğer öğe zaten mevcutsa adedini güncelleyin.*/
			 /* Overload += operator which merges two collections [25 points]
			 / if an item in the otherCollection is already in the collection than only increase the item count
			 / otherwise add the item as a new item*/
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

	/* Koleksiyondan bir diğer koleksiyonu çıkartan -= operatörünü aşırı yükleyin [30 Puan]
	  Eğer çıkartılacak öğe koleksiyonda yoksa bir şey yapılmaz,
	  çıkartılacak öğenin adedi mevcuttan fazlaysa/mevcuda eşitse öğe koleksiyondan çıkartılır,
	  çıkartılacak öğenin adedi mevcuttan azsa sadece adet güncellenir.
	  */
	  /* Overload -= operator which removes an item from the collection
	   if an item that you need to remove is not a member of the collection than ignore that item
	   if given item has equal or more number of instances than the collection has
	   then you must completly remove the item from the collection otherwise only update the item count*/
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
    } // 30 points


private:
	// numberOfUniqueItems koleksiyondaki Item sayısını tutar, TOPLAM ÖĞE SAYISINI değil
	// numberOfUniqueItems holds unique items not the total number of items in the collection
	int numberOfUniqueItems=0;
	Item * items;

	// Isterseniz buraya yardımcı fonksiyonlar yazabilirsiniz.
	// If you want you can write helper functions here.

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