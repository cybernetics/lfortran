subroutine sum_reduce(a, s)
real, intent(in) :: a(:)
real, intent(out) :: s
integer :: N, i
N = size(a)
s = 0
do concurrent (i = 1:N) reduce(*: s)
    s = s + a(i)
end do
do concurrent (i = 1:N) reduce(MIN: s)
    s = s + a(i)
end do
do concurrent (i = 1:N) reduce(MAX: s)
    s = s + a(i)
end do
end subroutine
