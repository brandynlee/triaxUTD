module triaxUTD

interface

  subroutine triaxUTD_setup() bind(c, name="triaxUTD_setup")
	use iso_c_binding
	implicit none
  end subroutine

  function triaxUTD_lnlikelihood(c, r200, a_b, b, phi, sintheta) bind(c, name="triaxUTD_lnlikelihood")
	use iso_c_binding
	implicit none
	real(c_double) :: triaxUTD_lnlikelihood
	real(c_double), value :: c
	real(c_double), value :: r200
	real(c_double), value :: a_b
	real(c_double), value :: b
	real(c_double), value :: phi
	real(c_double), value :: sintheta
  end function

end interface

end module triaxUTD
