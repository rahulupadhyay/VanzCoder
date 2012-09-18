program Principal;

{$mode objfpc}{$H+}

uses
  Classes, SysUtils, CustApp, Lista;

type

  L1221E25 = class(TCustomApplication)
  private
    lista : TLista;
    Procedure executa;
    
  protected
    procedure DoRun; override;
  end;

procedure L1221E25.executa;
var
  leitura : string;
begin
   lista := TLista.Create();
   WriteLn('L1221E25 - José Guilherme Vanz');
   WriteLn('Informe o nome das cidades ( Para terminar tecle ENTER vazio ): ');
   leitura := '';
   ReadLn(leitura);
	    
   while Length(leitura) <> 0 do
   begin
      lista.adiciona(leitura);
      ReadLn(leitura);
   end;
	Writeln(lista.imprime);
	lista.limpa();
	Halt;
end;


procedure L1221E25.DoRun;
begin
  executa;
end;

var
  Application: L1221E25;
begin
  Application:=L1221E25.Create(nil);
  Application.Run;
  Application.Free;
end.

