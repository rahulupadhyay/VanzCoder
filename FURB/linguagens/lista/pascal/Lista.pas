unit Lista;

{$mode objfpc}{$H+}

interface
uses
  Classes, SysUtils, NoLista;

type
   { TLista }
   TLista = class

   Private
     prim: TNoLista;
   Public
     procedure adiciona(element: String);
     procedure limpa();
     function imprime: String;
     constructor Create();
   end;

implementation

procedure TLista.adiciona(element : String);

var x,
    atu,
    ant : TNoLista;
begin
  x := TNoLista.Create(element);
  atu := prim;
  ant := nil;
  if prim = nil then
  begin
    prim:= x;
  end
  else
  begin
    while atu <> nil do
    begin
      if atu.getValor > element then
      begin
        if ant <> nil then
        begin
          ant.setProximo(x);
          x.setProximo(atu);
          Exit();
        end
        else
        begin
          x.setProximo(atu);
          prim := x;
          Exit();
        end;
      end
      else
      begin
         ant := atu;
         atu := atu.getProximo;
         if atu = nil then
         begin
           ant.setProximo(x);
           Exit();
         end;
      end;
    end;
  end;
end;

procedure TLista.limpa();
begin
     prim := nil;
end;

function TLista.imprime: String;
var prox : TNoLista;
    x: String;
begin
  x := 'INICIO DA LISTAGEM '+ #13#10#13#10;
  prox := prim;
  while prox <> nil do
  begin
    Insert(prox.getValor+#13#10, x, Length(x));
    prox := prox.getProximo;
  end;
  Insert('FIM DA LISTAGEM', x, Length(x));
  Result := x;
end;

constructor TLista.Create();
begin
   prim := nil;
end;

end.
