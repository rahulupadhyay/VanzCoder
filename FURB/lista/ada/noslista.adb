package body NosLista is

	function make(valor_no : Integer) return NoLista is
			o:NoLista;
		begin
			o.valor := valor_no;
			return o;
		end make; 

	function get_valor(This : NoLista) return Integer is
		begin
			return This.valor;
		end get_valor;

end NosLista;
