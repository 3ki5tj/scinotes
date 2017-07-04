#!/usr/bin/env python



r'''
Check all equations are used.
'''



import sys, os, getopt, shutil, re



fninp = None
verbose = 0



def usage():
  ''' print usage and die '''

  print """  Usage:
    %s [OPTIONS]""" % sys.argv[0]

  print """
  remove annotations in the tex file

  OPTIONS:
    -i              set the input file
    -v              be more verbose
    --verbose=      set verbosity
    -h, --help      help
  """
  exit(1)



def doargs():
  ''' handle input arguments '''
  try:
    opts, args = getopt.gnu_getopt(sys.argv[1:],
        "i:v",
        [ "help", "verbose=",
        ] )
  except getopt.GetoptError, err:
    print str(err)
    usage()

  global fninp, verbose

  for o, a in opts:
    if o in ("-v",):
      verbose += 1  # such that -vv gives verbose = 2
    elif o in ("--verbose",):
      verbose = int(a)
    elif o in ("-i",):
      fninp = a
    elif o in ("-h", "--help"):
      usage()

  if len(args):
    fninp = args[0]


def incomment(s, pos):
  ''' check if s[pos] is in a comment line '''
  while pos >= 0:
    if s[pos] == '%':
      return True
    if s[pos] in "\n\r":
      break
    pos -= 1
  return False



def listeq(s, tag, pref):
  ''' check equation references '''
  pat = "%s{%s" % (tag, pref)

  pos = 0 # starting position

  ls = []
  while 1:
    pos = s.find(pat, pos)
    if pos < 0:
      break

    end = s.find("}", pos)
    if end < 0:
      break

    name = s[pos + len(tag) + 1 : end]

    # check if this line is in a comment
    if not incomment(s, pos):
      ls += [ name, ]

    pos += len(tag)
  return ls



def checkuse1(s, tag):
  ''' check if the tag exists '''
  pos = 0
  while 1:
    pos = s.find(tag, pos)
    if pos < 0:
      break
    if not incomment(s, pos):
      return True
    pos += len(tag)
  return False



def checkuse(s, ls):
  ''' check if equation labels are used '''
  use = {}
  for name in ls:
    if checkuse1(s, "\\eqref{" + name):
      use[name] = 1
    elif checkuse1(s, "\\ref{" + name):
      use[name] = 1
    else:
      print "%s is unused" % name
      use[name] = 0
  return use


def main():
  global fninp

  s = open(fninp).read()

  ls = listeq(s, "\label", "eq:")
  print "%s equation labels" % len(ls)

  use = checkuse(s, ls)




if __name__ == "__main__":
  doargs()
  main()

