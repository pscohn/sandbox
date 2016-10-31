def reverse_polish_notation
  loop do
    stack = []
    gets.chomp.split.each do |tok|
      case tok
      when '+'
        stack.push(stack.pop + stack.pop)
      when '-'
        stack.push(stack.pop - stack.pop)
      when '*'
        stack.push(stack.pop * stack.pop)
      when '/'
        stack.push(stack.pop / stack.pop)
      else
        stack.push tok.to_i
      end
    end
    p stack
  end
end

class InputStream
  def initialize(input)
    @input = input
    @pos = 0
    @line = 1
    @col = 0
  end

  def next
    char = @input[@pos]
    @pos += 1
    if char == '\n'
      @line += 1
      @col = 0
    else
      @col += 1
     end
     char
  end

  def peek
    @input[@pos]
  end

  def eof
    peek == '' || peek == nil
  end

  def croak msg
    raise StandardError, "#{msg} (#{@line}:#{@col})"
  end
end

class TokenStream
  attr_accessor :current
  def initialize input
    @input = input
    @current = nil
    @keywords = " if then else lambda true false "
  end

  def croak msg
    raise StandardError, "#{msg} (#{@current})"
  end

  def is_keyword x
    @keywords.include? " #{x} "
  end

  def is_digit ch
    !!(/[0-9]/.match ch)
  end

  def is_id_start ch
    !!(/[a-z_]/i.match ch)
  end

  def is_id ch
    return is_id_start(ch) || ("?!-<>=0123456789".include? ch)
  end

  def is_op_char ch
    "+-*/%=&|<>!".include? ch
  end

  def is_punc ch
    ",;(){}[]".include? ch
  end

  def is_whitespace ch
    " \t\n".include? ch
  end

  def read_while &block
    str = ''
    while !@input.eof && block.call(@input.peek) do
      str += @input.next()
    end
    str
  end

  def read_number
    has_dot = false
    number = read_while do |ch|
      if ch == '.'
        return false if has_dot
        has_dot = true
        return true
      end
      return is_digit(ch)
    end
    return { type: 'num', value: parseFloat(number) }
  end

  def read_ident
    id = read_while do |ch|
      is_id ch
    end
    return {
      type: is_keyword(id) ? 'kw' : 'var',
      value: id
    }
  end

  def read_escaped(last)
    escaped = false
    str = ''
    @input.next
    while !@input.eof() do
      ch = @input.next()
      if escaped
        str += ch
        escaped = false
      elsif ch == '\\'
        escaped = true
      elsif ch == last
        break
      else
        str += ch
      end
    end
    str
  end

  def read_string
    return { type: 'str', value: read_escaped('"')}
  end

  def skip_comment
    read_while do |ch|
      return ch != '\n'
    end
    @input.next()
  end

  def read_next
    read_while do |ch|
      is_whitespace ch
    end
    return nil if @input.eof()
    ch = @input.peek
    if ch == '#'
      skip_comment
      return read_next
    end
    return read_string if ch == '"'
    return read_number if is_digit ch
    return read_ident if is_id_start ch
    if is_punc ch
      return { type: 'punc', value: @input.next }
    end
    if is_op_char ch
      return { type: 'op', value: read_while { |ch| is_op_char ch } }
    end
    @input.croak("cannot handle character: #{ch}")
  end

  def peek
    return @current || (@current = read_next)
  end

  def next
    tok = @current
    @current = nil
    return tok || read_next
  end

  def eof
    peek == nil
  end
end

FALSEY = { type: 'bool', value: false }
PRECEDENCE = {
  "=" => 1,
  "||" => 2,
  "&&" => 3,
  "<" => 7, ">" => 7, "<=" => 7, ">=" => 7, "==" => 7, "!=" => 7,
  "+" => 10, "-" => 10,
  "*" => 20, "/" => 20, "%" => 20,
}
class Parser
  def initialize input
    @input = input
  end

  def parse
    parse_toplevel
  end

  def is_punc ch
    tok = @input.peek
    tok && tok[:type] == 'punc' && (!ch || tok[:value] == ch) && tok
  end

  def is_kw kw
    tok = @input.peek
    tok && tok[:type] == "kw" && (!kw || tok[:value] == kw) && tok
  end

  def is_op op=nil
    tok = @input.peek
    return tok && tok[:type] == "op" && (!op || tok[:value] == op) && tok
  end

  def skip_punc(ch)
    if is_punc(ch)
      @input.next()
    else
      @input.croak("Expecting punctuation: \"" + ch + "\"")
    end
  end

  def skip_kw(kw)
    if is_kw kw
      @input.next
    else
      @input.croak("Expecting keyword: \"" + kw + "\"")
    end
  end

  def skip_op(op)
    if is_op(op)
      @input.next()
    else
      @input.croak("Expecting operator: \"" + op + "\"")
    end
  end

  def unexpected()
    @input.croak("Unexpected token: " + @input.peek())
  end

  def maybe_binary(left, my_prec)
    tok = is_op()
    if (tok)
      his_prec = PRECEDENCE[tok[:value]]
      if his_prec > my_prec
        @input.next()
        return maybe_binary({
          type: tok[:value] == "=" ? "assign" : "binary",
          operator: tok[:value],
          left: left,
          right: maybe_binary(parse_atom(), his_prec)
        }, my_prec)
      end
    end
    left
  end

  def delimited(start, stop, separator, &parser)
    a = []
    first = true
    skip_punc(start)
    while !@input.eof() do
      if is_punc(stop)
        break
      end
      if first
        first = false
      else
        skip_punc(separator)
      end
      if is_punc(stop)
        break
      end
      a.push(parser.call)
    end
    skip_punc(stop)
    a
  end

  def parse_call(func)
    parser = Proc.new { parse_expression }
    return {
      type: "call",
      func: func,
      args: delimited("(", ")", ",", parser),
    }
  end

  def parse_varname()
    name = @input.next()
    if name[:type] != "var"
      @input.croak("Expecting variable name")
    end
    name.value
  end

  def parse_if()
    skip_kw("if")
    cond = parse_expression()
    if !is_punc("{")
      skip_kw "then"
    end
    _then = parse_expression()
    ret = {
        type: "if",
        cond: cond,
        then: _then,
    }
    if is_kw("else")
      @input.next()
      ret.else = parse_expression()
    end
    ret
  end

  def parse_lambda()
    parser = Proc.new { parse_varname }
    return {
      type: "lambda",
      vars: delimited("(", ")", ",", parser),
      body: parse_expression()
    }
  end

  def parse_bool()
    return {
      type: "bool",
      value: @input.next().value == "true"
    }
  end

  def maybe_call(&expr)
    expr = expr.call
    is_punc("(") ? parse_call(expr) : expr
  end

  def parse_atom()
    maybe_call do
      if is_punc("(")
        @input.next()
        exp = parse_expression()
        skip_punc(")")
        return exp
      end
      return parse_prog() if is_punc("{")
      return parse_if() if is_kw("if")
      return parse_bool() if is_kw("true") || is_kw("false")
      if is_kw("lambda") || is_kw("λ")
          @input.next()
          return parse_lambda()
      end
      tok = @input.next()
      return tok if (tok[:type] == "var" || tok[:type] == "num" || tok[:type] == "str")
      unexpected()
    end
  end

  def parse_toplevel
    prog = []
    while !@input.eof do
      prog.push(parse_expression())
      puts prog.last
      if !@input.eof
        skip_punc(";")
      end
    end
    { type: "prog", prog: prog }
  end

  def parse_prog
    prog = delimited("{", "}", ";", Proc.new { parse_expression })
    return FALSEY if prog.length == 0
    return prog[0] if prog.length == 1
    { type: "prog", prog: prog }
  end

  def parse_expression()
    return maybe_call do
      return maybe_binary(parse_atom(), 0)
    end
  end
end

class Environment
  def initialize parent
    @vars = parent&.vars
    @parent = parent
  end
end

def read_file
  f = File.read 'file.fake'
  #puts f
  f
end


file = read_file
input = InputStream.new file
tokens = TokenStream.new input
parser = Parser.new(tokens)
ast = parser.parse
puts ast