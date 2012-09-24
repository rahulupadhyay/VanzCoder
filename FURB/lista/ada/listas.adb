with Gnat.Io; use Gnat.Io;

package body Listas is

	function make return Lista is
		o : Lista;
	begin
		o.inicio := null;
		return o;
	end make;

	procedure adiciona(This : in out Lista; valor : String) is
		Novo_No : No_Ptr;
		No_Atual : No_Ptr := This.inicio;
	begin
		Novo_No := new No'(valor,null);
		if No_Atual = null then
			This.inicio := Novo_No;
			return;
		end if;
		loop
			exit when No_Atual = null;
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
			Put_Line(No_Atual.valor);
			No_Atual := No_Atual.proximo;
		end loop;
		put_line("FIM DA LISTAGEM");
	end imprime;

end Listas;
