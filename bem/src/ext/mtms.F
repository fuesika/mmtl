      SUBROUTINE MTMS (M, N, L, A, KA, B, KB, C, KC)
C-----------------------------------------------------------------------
C                     PRODUCT OF REAL MATRICES
C-----------------------------------------------------------------------
      REAL, intent(in)  :: A(KA,N), B(KB,L)
      REAL, intent(out) :: C(KC,L)
      DOUBLE PRECISION  :: W, W_ABS
C
      DO 30 J = 1,L
         DO 20 I = 1,M
            W = 0.D0
            DO 10 K = 1,N
               W = W + DBLE(A(I,K))*DBLE(B(K,J))
   10       CONTINUE
c           sanity check to avoid unnoticed overflow
            W_ABS = abs(W)
            if ((W_ABS > 1.D35) .or. (W_ABS < 1.D-35)) then 
              stop 'critical: subsequent conv may lead to overflow'
            end if
            C(I,J) = real(W)
   20    CONTINUE
   30 CONTINUE
      RETURN
      END
