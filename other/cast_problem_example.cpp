    #include <stdio.h>
    #include <stdlib.h>
     
    //interface para cachorros
    class IDog {
    public:
        virtual ~IDog() { } 
        virtual void bark() = 0;
    };
    //implementação de um cachorro base
    class Dog : public IDog {
    public:
        virtual void bark() { puts("au, au au au!"); } //latindo em português
    };
     
    //interface para gatos
    class ICat {
    public:
        virtual ~ICat() { } 
        virtual void mew() = 0;
    };
    //implementação de um gato base
    class Cat : public ICat {
    public:
        virtual void mew() { puts("meooowwww....!"); } //miando em inglês
    };
     
    //Catdog: se você já viu este desenho, sabe que ele é um cachorro e um gato. https://www.google.com/ncr#q=catdog
    class CatDog : public Cat, public Dog {
    };
     
    int main(int argc, char* argv[]) {
        //como nosso cachorro, vamos criar o CatDog o/
        IDog* aDog = new CatDog();
        aDog->bark();
     
        //hmm... o problema é que tem bastante gente que adora gatos também...
        //nossa sorte é que temos CatDog, na variável 'aDog', certo? =)
        ICat* aCat = (ICat*)aDog;
        aCat->mew();
     
        delete aDog;
        return EXIT_SUCCESS;
    }


