package body NosLista is

	function make(valor_no : String)
	return NoLista is
			o:NoLista;
		begin
			o.set_valor(valor_no);
			return o;
		end make; 

	function get_valor(This : NoLista)
	return String is
		begin
			return This.valor;
		end get_valor;

	procedure set_valor(This : in out NoLista;  novo_valor : String) is
	begin
		This.valor := novo_valor;
	end set_valor;

end NosLista;
