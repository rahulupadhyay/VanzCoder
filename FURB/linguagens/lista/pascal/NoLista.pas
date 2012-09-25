unit NoLista;
{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils; 

type
   { TNoLista }
   TNoLista = class

   Private

     valor: String;
     proximo: TNoLista;

   Public

     procedure setValor(element: String);
     procedure setProximo(pro: TNoLista);
     function getProximo: TNoLista;
     function getValor: String;
     constructor Create(element: String);

   end;

implementation

procedure TNoLista.setValor(element: String);
begin
  valor:=element;
end;

procedure TNoLista.setProximo(pro:TNoLista);
begin
  proximo:=pro;
end;

function TNoLista.getProximo: TNoLista;
begin
  Result := proximo;
end;

function TNoLista.getValor: String;
begin
   Result := valor
end;

constructor TNoLista.Create(element:String);
begin
  valor:=element;
  proximo:=nil;
end;

end.


