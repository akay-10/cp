#!/bin/bash

# =============================================================================
# run.sh — Competitive Programming build & run script
# Usage:
#   ./run.sh                        # local mode, compiles code.cc
#   ./run.sh local                  # local mode, compiles code.cc
#   ./run.sh judge                  # judge mode, compiles code.cc
#   ./run.sh local myfile.cc        # local mode, compiles myfile.cc
#   ./run.sh judge myfile.cc        # judge mode, compiles myfile.cc
#   ./run.sh myfile.cc              # local mode (default), compiles myfile.cc
# =============================================================================

MODE="local"     # default mode
SOURCE="code.cpp" # default source file

# Color output. Init colors only when this process's fd 1 (stdout) is connected
# to a terminal.
if [[ -t 1 ]]; then
  RED='\033[0;31m'
  GREEN='\033[0;32m'
  YELLOW='\033[1;33m'
  BLUE='\033[0;34m'
  CYAN='\033[0;36m'
  MAGENTA='\033[0;35m'
  NC='\033[0m'
else
  RED=''
  GREEN=''
  YELLOW=''
  BLUE=''
  CYAN=''
  MAGENTA=''
  NC=''
fi

# Logging functions
log_info() {
  echo -e "${BLUE}[INFO]${NC} $1"
}

log_success() {
  echo -e "${GREEN}[SUCCESS]${NC} $1"
}

log_warning() {
  echo -e "${YELLOW}[WARNING]${NC} $1"
}

log_error() {
  echo -e "${RED}[ERROR]${NC} $1"
}

log_debug() {
  if [ "$VERBOSE" = true ]; then
    echo -e "${MAGENTA}[DEBUG]${NC} $1" >&2
  fi
}

log_separator() {
  echo -e "${CYAN}=========================================${NC}"
}

log_test_header() {
  log_separator
  echo -e "${CYAN}Running: ${MAGENTA}$1${NC}"
  log_separator
}

# -----------------------------------------------------------------------------
# Argument parsing
# -----------------------------------------------------------------------------
for arg in "$@"; do
  if [ "$arg" = "local" ] || [ "$arg" = "judge" ]; then
    MODE="$arg"
  elif [[ "$arg" == *.cc ]] || [[ "$arg" == *.cpp ]]; then
    SOURCE="$arg"
  else
    log_error "Unknown argument: '$arg'"
    log_info "Usage: ./run.sh [local|judge] [filename.cc|filename.cpp]"
    exit 1
  fi
done

# -----------------------------------------------------------------------------
# Validate source file exists
# -----------------------------------------------------------------------------
if [ ! -f "$SOURCE" ]; then
  log_error "Error: Source file '$SOURCE' not found."
  exit 1
fi

# Derive output binary name from source file (strip extension)
BINARY="${SOURCE%.*}"

# -----------------------------------------------------------------------------
# Compile
# -----------------------------------------------------------------------------
if [ "$MODE" = "local" ]; then
  log_info "Running in LOCAL mode (with dbg.h) — $SOURCE"
  g++ -DLOCAL -std=c++17 -O2 -Wall -Wextra -o "$BINARY" "$SOURCE"
elif [ "$MODE" = "judge" ]; then
  log_info "Running in JUDGE mode (without dbg.h) — $SOURCE"
  g++ -std=c++17 -O2 -Wall -Wextra -o "$BINARY" "$SOURCE"
fi

# -----------------------------------------------------------------------------
# Check compilation result
# -----------------------------------------------------------------------------
if [ $? -ne 0 ]; then
  log_error "Compilation failed."
  exit 1
fi

# -----------------------------------------------------------------------------
# Run — use input.txt if it exists, otherwise use stdin
# -----------------------------------------------------------------------------
if [ -f "input.txt" ]; then
  log_success "Using input.txt..."
  ./"$BINARY" <input.txt
else
  log_info "No input.txt found, reading from stdin..."
  ./"$BINARY"
fi
