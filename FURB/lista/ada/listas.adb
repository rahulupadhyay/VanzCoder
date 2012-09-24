with Gnat.Io; use Gnat.Io;
with Ada.Strings.Unbounded;
use Ada.Strings.Unbounded;

package body Listas is

	function make return Lista is
		o : Lista;
	begin
		o.inicio := null;
		return o;
	end make;





	procedure adiciona(This : in out Lista; valor : Ada.Strings.Unbounded.Unbounded_String) is
		Novo_No : No_Ptr;
		No_Atual : No_Ptr := This.inicio;
		No_Anterior : No_Ptr := null;
	begin
		Novo_No := new No'(valor,null);
		if No_Atual = null then -- Primeiro no da lista
			This.inicio := Novo_No;
			This.tamanho := This.tamanho + 1;
			return;
		end if;
		loop
			exit when No_Atual = null;
			if Novo_No.valor < No_Atual.valor then
				if This.inicio = No_Atual then
					Novo_No.proximo := This.inicio;
					This.inicio := Novo_No;
					This.tamanho := This.tamanho + 1;	
					return;
				else
					Novo_No.proximo := No_Atual;
					No_Anterior.proximo := Novo_no;
					This.tamanho := This.tamanho + 1;
					return;
				end if;
			else
				if No_Atual.proximo = null then
					No_Atual.proximo := Novo_No;
					This.tamanho := This.Tamanho + 1;
					return;
				end if;
				No_Anterior := No_Atual;
				No_Atual := No_Atual.proximo;
			end if;



			if No_Atual.proximo = null then
				No_Atual.proximo := Novo_No;
				return;
			else
				No_Atual := No_Atual.proximo;
			end if;
		end loop;
	end adiciona;





	procedure imprime(This: in out Lista) is
		No_Atual : No_Ptr := This.inicio;
	begin
		put_line("INÍCIO DA LISTAGEM");
		loop
			exit when No_Atual = null;
			Put_Line(Ada.Strings.Unbounded.To_String(No_Atual.valor));
			No_Atual := No_Atual.proximo;
		end loop;
		put_line("FIM DA LISTAGEM");
	end imprime;



	procedure limpar(This : in out Lista) is
	begin
		This.inicio := null;
	end limpar;

end Listas;
