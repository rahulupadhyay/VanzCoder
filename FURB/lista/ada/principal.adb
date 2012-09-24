With Listas; use Listas; -- clase de lista
with Ada.Strings.Unbounded;
With Ada.Text_IO;
use Ada.Text_IO;

Procedure Principal is
	l : Lista := make;
	city : Ada.Strings.Unbounded.Unbounded_String;
	str : String(1 .. 255);
	len : Integer;
begin
	put_line("L1221D25 - José Guilherme Vanz");
	put_line("Informe o nome das cidades < ENTER vazio para finalizar >");
	loop
		Ada.Text_IO.Put("> ");
		Ada.Text_IO.Get_Line(str,len);
      		exit when len = 0;
		city := Ada.Strings.Unbounded.To_Unbounded_String(str(1 .. len));
		l.adiciona(city);
	end loop;
	l.imprime;
		
end Principal;
