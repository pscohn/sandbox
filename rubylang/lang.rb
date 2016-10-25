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
    peek == '';
  end

  def croak msg
    raise StandardError, "#{msg} (#{line}:#{col})"
  end
end

class TokenStream
  def initialize input
    @input = input
    @current = null
    @keywords = " if then else lambda true false "
  end

  def is_keyword x
    @keywords.include? " #{x} "
  end

  def is_digit ch
    !!/[0-9]/.match ch
  end

  def is_id_start ch
    !!/[a-z_]/i.match ch
  end

  def is_op_char ch
    "+-*/%=&|<>!".include? char
  end

  def is_punc ch
    ",;(){}[]".include? char
  end

  def is_whitespace ch
    " \t\n".include? ch
  end

  def read_while predicate
    str = '';
    while !input.eof && predicate(input.peek) do
      str += input.next()
    end
    str
  end

  def read_number
    has_dot = false
    number = read_while
  end

  def read_ident
  end

  def read_escaped end
  end

  def read_string
  end

  def skip_comment
  end

  def read_next
  end

  def peek
  end

  def next
  end

  def eof
  end
end


def read_file
  f = File.read 'file.fake'
  puts f
end

read_file