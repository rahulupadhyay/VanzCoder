package NosLista is
	type NoLista is tagged 
		record   
			valor : String;
		end record;
	function make(valor_no : String) 
		return NoLista;
	function get_valor(This : NoLista)
		return String;

	procedure set_valor(This : in out  NoLista; novo_valor : String );
end NosLista;
