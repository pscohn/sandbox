def run
  loop do
    print '> '
    array = parse_input gets.chomp
    permutations = permutate array
    print permutations
    puts ''
  end
end

def parse_input input
  input.split
end

def permutate array
  
end

run
