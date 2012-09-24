With Listas; use Listas; -- clase de lista
with Gnat.Io; use Gnat.Io;

Procedure Principal is
	l : Lista := make;
	city : String(1 .. 255);
	len : Integer;
begin
	put_line("L1221D25 - José Guilherme Vanz");
	put_line("Informe o nome das cidades < ENTER vazio para finalizar >");
	loop
		Put("> ");
		Get_Line(city,len);
      		exit when len = 0;
		l.adiciona(city);
	end loop;
	l.imprime;
		
end Principal;
